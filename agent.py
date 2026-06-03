"""
cpp-learning Repository Agent
==============================
Automates:
  - Generating / regenerating chapter-specific README.md files using Ollama
  - Updating the global README.md (repo tree + progress tracker)
  - Git push

Usage:
    python agent.py              # Normal run
    python agent.py --dry-run    # Preview only — no file writes, no git ops
"""

import os
import sys
import json
import re
import subprocess
import urllib.request
from pathlib import Path
from datetime import datetime

# ─────────────────────────────────────────────
#  CONFIG
# ─────────────────────────────────────────────

REPO_ROOT       = Path(__file__).parent.resolve()
FLAGS_FILE      = REPO_ROOT / "flags.json"
GLOBAL_README   = REPO_ROOT / "README.md"

# Match numbered chapter folders like 03_debugging, 04_data_types …
CHAPTER_PATTERN = re.compile(r"^\d{2}_")

# Ollama — qwen3:8b fits comfortably in RTX 4060 8GB VRAM
OLLAMA_URL   = "http://localhost:11434/api/chat"
OLLAMA_MODEL = "qwen3:8b"

DRY_RUN = "--dry-run" in sys.argv


# ─────────────────────────────────────────────
#  OLLAMA
# ─────────────────────────────────────────────

def init_ollama() -> None:
    """Verify Ollama is running and the model is available."""
    try:
        req = urllib.request.Request("http://localhost:11434/api/tags")
        with urllib.request.urlopen(req, timeout=5) as res:
            data   = json.loads(res.read())
            models = [m["name"] for m in data.get("models", [])]
            if not any(OLLAMA_MODEL in m for m in models):
                print(f"[ERROR] Model '{OLLAMA_MODEL}' not found.")
                print(f"  Available: {models}")
                print(f"  Run: ollama pull {OLLAMA_MODEL}")
                sys.exit(1)
            print(f"  [OLLAMA] Model ready: {OLLAMA_MODEL}")
    except Exception:
        print("[ERROR] Ollama is not running.")
        print("  Run: ollama serve   (or open the Ollama app on Windows)")
        sys.exit(1)


def ollama_generate(prompt: str) -> str:
    """Send a prompt to Ollama; return the response text."""
    payload = json.dumps({
        "model":   OLLAMA_MODEL,
        "messages": [{"role": "user", "content": prompt}],
        "stream":  False,
        "think":   False,
        "options": {"temperature": 0.2, "num_predict": 4096},
    }).encode("utf-8")

    req = urllib.request.Request(
        OLLAMA_URL,
        data=payload,
        headers={"Content-Type": "application/json"},
    )
    with urllib.request.urlopen(req, timeout=120) as res:
        raw = json.loads(res.read())["message"]["content"].strip()

    # Strip <think>...</think> block if model still outputs it
    raw = re.sub(r"<think>.*?</think>", "", raw, flags=re.DOTALL).strip()
    return raw


# ─────────────────────────────────────────────
#  FLAGS  (flags.json)
# ─────────────────────────────────────────────

def load_flags() -> dict:
    """
    Minimal flags.json schema:
    {
        "completed":  ["03_debugging", "04_data_types"],
        "summarized": ["03_debugging"],
        "last_run":   "2025-06-01T12:00:00"
    }
    """
    if not FLAGS_FILE.exists():
        default = {"completed": [], "summarized": [], "last_run": None}
        FLAGS_FILE.write_text(json.dumps(default, indent=2))
        return default
    flags = json.loads(FLAGS_FILE.read_text())
    # Ensure keys exist even in old flags files
    flags.setdefault("completed",  [])
    flags.setdefault("summarized", [])
    return flags


def save_flags(flags: dict) -> None:
    flags["last_run"] = datetime.now().isoformat()
    if not DRY_RUN:
        FLAGS_FILE.write_text(json.dumps(flags, indent=2))


# ─────────────────────────────────────────────
#  REPO SCANNING
# ─────────────────────────────────────────────

def get_chapter_folders() -> list[Path]:
    return sorted(
        p for p in REPO_ROOT.iterdir()
        if p.is_dir() and CHAPTER_PATTERN.match(p.name)
    )


def get_cpp_files(folder: Path) -> list[Path]:
    return sorted(folder.glob("*.cpp"))


# ─────────────────────────────────────────────
#  STEP 1: GENERATE CHAPTER README
# ─────────────────────────────────────────────

CHAPTER_README_PROMPT = """\
You are writing a chapter summary README.md for a C++ learning repository.
Chapter: {chapter_name}

Below are all the .cpp source files the student wrote for this chapter:

{all_files}

Write a comprehensive but concise Markdown README.md that:
1. Opens with a # heading equal to the chapter name.
2. Has a "## Key Concepts" section listing what was learned.
3. Has a "## Critical Insights" section with 2-3 code snippets (```cpp fences)
   highlighting non-obvious or important patterns — prefer ❌/✅ contrasts or
   KEY INSIGHT blocks if present in the source files.
4. Has a "## Files in this Chapter" table:
   | File | What it demonstrates |
5. Ends with "## What to Remember" — max 3 bullets covering common pitfalls.

Tone: clear, technical, no filler. Write as if explaining to a fellow CSE student.
Output ONLY raw Markdown. No preamble, no explanation outside the document.
"""


def generate_chapter_readme(folder: Path) -> bool:
    cpp_files = get_cpp_files(folder)
    if not cpp_files:
        print(f"  [SKIP] {folder.name} — no .cpp files found.")
        return False

    print(f"  [README] Generating chapter README for {folder.name} …")

    combined = ""
    for f in cpp_files:
        combined += f"\n\n--- FILE: {f.name} ---\n"
        combined += f.read_text(encoding="utf-8")

    prompt = CHAPTER_README_PROMPT.format(
        chapter_name=folder.name,
        all_files=combined,
    )

    try:
        content = ollama_generate(prompt)
        readme_path = folder / "README.md"
        if not DRY_RUN:
            readme_path.write_text(content, encoding="utf-8")
            print(f"  [OK] {folder.name}/README.md written.")
        else:
            print(f"  [DRY-RUN] Would write {folder.name}/README.md")
        return True
    except Exception as e:
        print(f"  [ERROR] Could not generate README for {folder.name}: {e}")
        return False


# ─────────────────────────────────────────────
#  STEP 2: UPDATE GLOBAL README
# ─────────────────────────────────────────────

def build_repo_tree(chapter_folders: list[Path]) -> str:
    """Return a Markdown code block showing the repo directory tree."""
    lines = ["```", f"{REPO_ROOT.name}/"]
    for folder in chapter_folders:
        cpp_files = get_cpp_files(folder)
        readme    = folder / "README.md"
        lines.append(f"├── {folder.name}/")
        for f in cpp_files:
            lines.append(f"│   ├── {f.name}")
        if readme.exists():
            lines.append(f"│   └── README.md")
    lines += ["├── README.md", "├── flags.json", "└── agent.py", "```"]
    return "\n".join(lines)


def folder_to_ch_num(folder_name: str) -> str:
    return folder_name.split("_")[0].lstrip("0") or "0"


def update_global_readme(chapter_folders: list[Path], completed: list[str]) -> None:
    """
    Updates two sections in the global README.md:
      1. A fenced repo-tree block between <!-- REPO_TREE_START --> and <!-- REPO_TREE_END -->
      2. Progress-tracker table rows (| Ch.X | … |)

    If those comment markers don't exist the tree section is silently skipped;
    the table rows are always updated when found.
    """
    print("\n[STEP 2] Updating global README.md …")

    if not GLOBAL_README.exists():
        print("  [WARN] README.md not found at repo root — skipping global update.")
        return

    readme = GLOBAL_README.read_text(encoding="utf-8")

    # ── 2a. Repo tree ──────────────────────────────────────────────────────
    tree_block = build_repo_tree(chapter_folders)
    tree_pattern = re.compile(
        r"(<!-- REPO_TREE_START -->).*?(<!-- REPO_TREE_END -->)",
        re.DOTALL,
    )
    if tree_pattern.search(readme):
        readme = tree_pattern.sub(
            rf"\1\n{tree_block}\n\2",
            readme,
        )
        print("  [OK] Repo tree section updated.")
    else:
        print("  [INFO] No <!-- REPO_TREE_START/END --> markers found — skipping tree update.")
        print("         Add these markers to README.md where you want the tree rendered.")

    # ── 2b. Progress tracker table rows ───────────────────────────────────
    # Build lookup: ch_number -> (file_count, status_cell)
    folder_map: dict[str, tuple[int, str]] = {}
    for folder in chapter_folders:
        ch_num    = folder_to_ch_num(folder.name)
        cpp_count = len(get_cpp_files(folder))
        is_done   = (folder.name in completed) or any(
            c.lstrip("0") == ch_num for c in completed
        )
        if is_done:
            status = "`✅ Done`"
        elif cpp_count > 0:
            status = "`🔄 In Progress`"
        else:
            status = "`⬜ Upcoming`"
        folder_map[ch_num] = (cpp_count, status)

    def replace_row(match: re.Match) -> str:
        row = match.group(0)
        ch_match = re.search(r"Ch\.(\d+)", row)
        if not ch_match:
            return row
        ch_num = ch_match.group(1)
        if ch_num not in folder_map:
            return row
        count, status = folder_map[ch_num]
        parts = [p.strip() for p in row.split("|")]
        # Expected format: | Ch.X | Topic | Status | Files |
        if len(parts) >= 5:
            parts[3] = f" {status} "
            parts[4] = f" {count} "
            return "| " + " | ".join(p.strip() for p in parts[1:5]) + " |"
        return row

    updated = re.sub(r"\| Ch\.\d+ \|[^\n]+\|", replace_row, readme)

    if updated == readme:
        print("  [INFO] Progress table — no changes needed.")
    else:
        print("  [OK] Progress table rows updated.")

    if not DRY_RUN:
        GLOBAL_README.write_text(updated, encoding="utf-8")
    else:
        print("  [DRY-RUN] Would write updated global README.md")


# ─────────────────────────────────────────────
#  STEP 3: GIT PUSH
# ─────────────────────────────────────────────

def git_push(summarized_chapters: list[str]) -> None:
    if DRY_RUN:
        print("\n[DRY-RUN] Would run: git add . && git commit && git push")
        return

    print("\n[STEP 3] Running git operations …")

    result = subprocess.run(["git", "add", "."], cwd=REPO_ROOT,
                            capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  [ERROR] git add failed:\n{result.stderr}")
        return

    if summarized_chapters:
        msg = f"[Agent] READMEs updated: {', '.join(summarized_chapters)}"
    else:
        msg = "[Agent] Global README progress tracker updated"

    result = subprocess.run(["git", "commit", "-m", msg], cwd=REPO_ROOT,
                            capture_output=True, text=True)
    if result.returncode != 0:
        if "nothing to commit" in result.stdout + result.stderr:
            print("  [INFO] Nothing to commit — working tree clean.")
            return
        print(f"  [ERROR] git commit failed:\n{result.stderr}")
        return

    print(f"  [OK] Committed: {msg}")

    result = subprocess.run(["git", "push"], cwd=REPO_ROOT,
                            capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  [ERROR] git push failed:\n{result.stderr}")
        print("  Tip: check your remote with 'git remote -v' and ensure auth is set up.")
        return

    print("  [OK] Pushed to remote.")


# ─────────────────────────────────────────────
#  MAIN
# ─────────────────────────────────────────────

def main() -> None:
    print("=" * 55)
    print("  cpp-learning Agent")
    if DRY_RUN:
        print("  MODE: DRY RUN — no files will be written")
    print("=" * 55)

    flags     = load_flags()
    completed = flags["completed"]
    print(f"\nCompleted chapters: {completed or 'none yet'}")

    init_ollama()

    chapter_folders = get_chapter_folders()
    if not chapter_folders:
        print("[ERROR] No chapter folders found. Run from the repo root.")
        sys.exit(1)

    print(f"Found {len(chapter_folders)} chapter folder(s).\n")

    summarized_chapters: list[str] = []

    # ── Per-chapter README generation ────────────────────────────────────
    for folder in chapter_folders:
        cpp_files = get_cpp_files(folder)
        if not cpp_files:
            print(f"[Chapter] {folder.name} — no .cpp files, skipping.")
            continue

        print(f"[Chapter] {folder.name} ({len(cpp_files)} file(s))")

        is_done      = folder.name in completed
        readme_path  = folder / "README.md"
        already_done = folder.name in flags["summarized"]

        if is_done:
            if not readme_path.exists() or not already_done:
                ok = generate_chapter_readme(folder)
                if ok:
                    summarized_chapters.append(folder.name)
                    if folder.name not in flags["summarized"]:
                        flags["summarized"].append(folder.name)
            else:
                print(f"  [SKIP] README already generated for {folder.name}.")
        else:
            print(f"  [INFO] Not marked done — skipping README generation.")
            print(f"         Add '{folder.name}' to flags.json > \"completed\" when finished.")

    # ── Global README ─────────────────────────────────────────────────────
    update_global_readme(chapter_folders, completed)

    # ── Git push ──────────────────────────────────────────────────────────
    git_push(summarized_chapters)

    # ── Save flags ────────────────────────────────────────────────────────
    save_flags(flags)

    print("\n" + "=" * 55)
    print("  Agent finished.")
    print("=" * 55)


if __name__ == "__main__":
    main()