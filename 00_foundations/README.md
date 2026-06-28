# 📘 C++ Notes — Chapter 0: Getting Started
> Source: [learncpp.com](https://www.learncpp.com) | Chapter 0 (Lessons 0.1–0.13)

---

## Table of Contents
- [0.1 — Welcome](#01--welcome)
- [0.2 — Programs & Programming Languages](#02--programs--programming-languages)
- [0.3 — Introduction to C/C++](#03--introduction-to-cc)
- [0.4 — C++ Development Process](#04--c-development-process)
- [0.5 — Compiler, Linker & Libraries](#05--compiler-linker--libraries)
- [0.6 — Installing an IDE](#06--installing-an-ide)
- [0.7 — Compiling Your First Program](#07--compiling-your-first-program)
- [0.8 — Common C++ Problems](#08--common-c-problems)
- [0.9 — Build Configurations](#09--build-configurations)
- [0.10 — Compiler Extensions](#010--compiler-extensions)
- [0.11 — Warning & Error Levels](#011--warning--error-levels)
- [0.12 — Choosing a Language Standard](#012--choosing-a-language-standard)
- [0.13 — Checking Your Language Standard](#013--checking-your-language-standard)

---

## 0.1 — Welcome

- These tutorials assume **zero prior programming experience**.
- Goals of learncpp.com:
    - Cover general programming topics (style, debugging, good/bad practices), not just syntax.
    - Provide lots of **examples** — no ellipsis tricks, no unexplained concepts.
    - Include **practice programs** with solutions at the end of most lessons.
    - Make learning **fun** — tired programmers make more bugs.

**How to learn effectively:**

| Practice | Why it helps |
|----------|--------------|
| Type examples by hand | Trains muscle memory, exposes common typos |
| Fix your own bugs first | Builds debugging instinct |
| Experiment with examples | Deepens real understanding |
| Write your own small programs | Reinforces and retains knowledge |

---

## 0.2 — Programs & Programming Languages

### Key Terms

| Term | Definition |
|------|-----------|
| **Computer program** | A sequence of instructions directing a computer to perform actions |
| **Programming language** | A language designed to write instructions for computers |
| **Running/executing** | When a computer performs the actions in a program |
| **Platform** | A compatible set of hardware + software (e.g., Windows on x86 CPU) |
| **Portable** | A program that can easily run on different platforms |

### Language Levels

#### Machine Language (Lowest Level)
- Only language CPUs natively understand
- Written in binary (1s and 0s): e.g., `10110000 01100001`
- Each CPU family has its own machine language — **not portable**
- Extremely hard to read/write for humans

#### Assembly Language
- Human-readable version of machine language
- Example: `mov al, 0x61` (same instruction as above)
- Still **not portable** — each CPU family has its own assembly
- Assembled into machine code by a program called an **assembler**

#### High-Level Languages (C, C++, Java, Python…)
- Abstracted from the hardware — no need to know the CPU architecture
- Example: `a = 97;` (one line vs 4–6 assembly instructions)
- **Portable** — one C++ program can compile on many platforms
- Translated to machine code in two ways:

```
Compiling:    Source Code → Compiler → Machine Code (executable)
Interpreting: Source Code → Interpreter → Executes directly (slower)
```

> ✅ **C++ is compiled.** The compiler translates your `.cpp` files into an executable.

### Why High-Level Languages Win
- Easier to read, write, and learn
- Fewer instructions needed for same tasks
- Compilers are now so good they often optimize better than humans

---

## 0.3 — Introduction to C/C++

### History of C
- Created in **1972** by **Dennis Ritchie** at Bell Labs
- Originally a **systems programming language** (written to build operating systems)
- Unix OS was rewritten in C in 1973 → made C hugely popular
- Standardized as **ANSI C / C90** in 1989–1990, updated to **C99** in 1999

### History of C++
- Created by **Bjarne Stroustrup** at Bell Labs starting in **1979**
- C++ = C + **Object-Oriented Programming (OOP)** + many other features
- Think of it as a superset of C (mostly)
- Standardized in **1998**, major updates: C++11, C++14, C++17, C++20, C++23

### C/C++ Philosophy
> "Trust the programmer."

- Gives maximum control and freedom
- Won't stop you from doing things that don't make sense
- ⚠️ Knowing what **NOT** to do is as important as knowing what to do

### What C++ Excels At
- Video games
- Real-time systems (transportation, manufacturing)
- High-performance financial apps (HFT)
- Graphical apps and simulations
- Embedded software
- Audio/video processing
- **AI and neural networks** 

### Is C++ Dying?
> ❌ No. Consistently ranked 2nd–3rd most popular compiled language. Updates every 3 years. Dominates game dev and systems programming.

---

## 0.4 — C++ Development Process

### The Full Development Cycle

```
Step 1: Define the problem
Step 2: Plan your solution
Step 3: Write the source code (.cpp files)
Step 4: Compile → object files (.o / .obj)
Step 5: Link object files + libraries → executable
Step 6: Test
Step 7: Debug
```

### Step 2 is the Most Neglected
Good solutions are:
- ✅ Straightforward — not overly complex
- ✅ Well-documented (assumptions, limitations noted)
- ✅ Modular — parts can be reused/changed without breaking others
- ✅ Graceful — handles unexpected input or errors

> ⚠️ Jumping straight to coding = technical debt, bugs, fragile programs.
> Studies show: **only 10–40%** of a programmer's time is writing new code. The rest is maintenance, debugging, and updates.

### Source Code File Naming
- Primary file: `main.cpp` (convention)
- Extension: `.cpp` (sometimes `.cc` or `.cxx`)
- C++ has no naming requirements, but the convention is widely followed

---

## 0.5 — Compiler, Linker & Libraries

### Step 4: Compilation

The **C++ compiler** does two things per `.cpp` file:
1. **Validates** your code against C++ language rules — emits errors if violated
2. **Translates** valid C++ into machine language → stores in an **object file** (`.o` / `.obj`)

```
main.cpp  →  [Compiler]  →  main.o
utils.cpp →  [Compiler]  →  utils.o
```

### Step 5: Linking

The **linker** combines all object files + libraries → final executable:

```
main.o + utils.o + [standard library] → MyProgram.exe
```

Linker tasks:
1. Validates all object files
2. Resolves **cross-file dependencies** (e.g., function defined in file A, used in file B)
3. Links in library files
4. Produces the output executable

### Libraries

| Type | Description |
|------|-------------|
| **C++ Standard Library** | Built-in — includes `iostream`, math, string, etc. Linked by default. |
| **3rd party libraries** | External — e.g., audio, graphics, networking. Must be linked manually. |

### Build vs Compile vs Run

| Action | What it does |
|--------|-------------|
| **Compile** | Recompiles a single file — no linker, no executable |
| **Build** | Compiles all modified files + links → produces executable |
| **Rebuild** | Clean + Build (recompiles everything from scratch) |
| **Clean** | Deletes all cached object files and executables |
| **Run/Start** | Executes the built executable |

### IDE = All-in-One
An **Integrated Development Environment (IDE)** bundles: editor + compiler + linker + debugger.

---

## 0.6 — Installing an IDE

### Recommended IDEs

| IDE | Platform | Notes |
|-----|----------|-------|
| **Visual Studio 2022 Community** | Windows | Best for Windows dev. Select "Desktop development with C++" workload during install. |
| **Code::Blocks** | Linux, Windows | Free, open source, cross-platform. Get the MinGW bundle on Windows. |
| **VS Code** | Linux, macOS, Windows | Fast & flexible but complex to configure. Not recommended for beginners. |
| **Xcode** | macOS | Good if available. |

> ✅ **Minimum requirement:** Compiler supporting **C++17** (GCC 7+, Clang 8+, VS 2017 15.7+)

### Web-Based Compilers (Temporary/Quick Use)
- [TutorialsPoint](https://www.tutorialspoint.com/online_compiler/online_c++-compiler.php)
- [Wandbox](https://wandbox.org/) — multiple GCC/Clang versions
- [Godbolt](https://godbolt.org/) — shows assembly output

> ⚠️ Web compilers don't support multi-file projects or interactive debugging.

---

## 0.7 — Compiling Your First Program

### Hello World

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!";
    return 0;
}
```

### Project Setup Steps (general flow)
1. Create a **new project** (console application type)
2. Each project = one program
3. Each project has its own compiler/linker settings
4. Name your first file `main.cpp`

> ✅ **Best Practice:** Create a new project for each new program.

### Console Closes Immediately Fix
Add this before `return 0;` in `main()`:

```cpp
#include <iostream>
#include <limits>

// At end of main(), before return:
std::cin.clear();
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
std::cin.get();
```

---

## 0.8 — Common C++ Problems

### Runtime Issues

| Problem | Fix |
|---------|-----|
| Console closes immediately | Add `cin.get()` at end of `main()` or run without debugging |
| Program runs but no output | Antivirus may be blocking — disable temporarily |

### Compile-Time Issues

| Error | Likely Cause |
|-------|-------------|
| `unresolved external symbol _main` | No `main()` function found — check spelling and file is in project |
| `main is already defined` | Multiple `main()` functions in your project — delete the extras |
| `Cannot open .exe for writing` | Executable is still running — close it first |
| `cin/cout is undeclared identifier` | Missing `#include <iostream>` or missing `std::` prefix |
| `end1 undeclared` | You typed the number `1` instead of lowercase letter `l` in `endl` |
| `C1010 precompiled header error` (VS) | Didn't turn off precompiled headers at project creation |

---

## 0.9 — Build Configurations

### Two Default Configurations

| Config | Purpose | Optimized? | Debug Info? |
|--------|---------|------------|-------------|
| **Debug** | Development — use this while writing code | ❌ No | ✅ Yes (larger file, slower) |
| **Release** | Distribution — use when shipping | ✅ Yes | ❌ No (smaller, faster) |

**Example (Hello World):**
- Debug build: ~65 KB
- Release build: ~12 KB

> ✅ **Best Practice:** Use **debug** while developing. Switch to **release** only for performance testing or distribution.

### GCC/Clang Optimization Flags

| Flag | Use |
|------|-----|
| `-O0` | No optimization (default, for debug) |
| `-O2` | Recommended for release |
| `-O3` | More aggressive — may or may not be faster than `-O2` (benchmark!) |
| `-ggdb` | Include debug info (for debug builds) |

---

## 0.10 — Compiler Extensions

- Compilers sometimes add **non-standard behaviors** beyond the C++ spec = **compiler extensions**
- Code using extensions may not compile on other compilers or produce different results
- Extensions are **enabled by default** — this is dangerous for new learners

> ✅ **Best Practice:** **Disable compiler extensions** to stay compliant with the C++ standard.

### How to Disable

| IDE / Compiler | Setting |
|----------------|---------|
| Visual Studio | C/C++ > Language > Conformance mode: `Yes (/permissive-)` |
| Code::Blocks | Settings > Compiler > Compiler flags: check `-pedantic-errors` |
| GCC / Clang | Add `-pedantic-errors` to compile command |
| VS Code | Add `"-pedantic-errors"` in `tasks.json` args |

---

## 0.11 — Warning & Error Levels

### Diagnostics: Errors vs Warnings

| Type | Behavior |
|------|----------|
| **Diagnostic Error** | Compiler halts — must fix before proceeding |
| **Diagnostic Warning** | Compiler continues — issue ignored but flagged |

> ⚠️ Warnings still matter. Don't ignore them — they often point to real bugs.

> ✅ **Best Practice:** Don't let warnings pile up. Treat them like errors.

### Increasing Warning Levels

| IDE / Compiler | Setting |
|----------------|---------|
| Visual Studio | C/C++ > General > Warning Level: `Level4 (/W4)` |
| Code::Blocks | Compiler flags: check `-Wall`, `-Weffc++`, `-Wextra`; add `-Wconversion -Wsign-conversion` |
| GCC / Clang | Add `-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion` |

### Treat Warnings as Errors (Recommended)

| IDE / Compiler | Setting |
|----------------|---------|
| Visual Studio | C/C++ > General > Treat Warnings As Errors: `Yes (/WX)` |
| Code::Blocks | Other compiler options: add `-Werror` |
| GCC / Clang | Add `-Werror` |

---

## 0.12 — Choosing a Language Standard

### C++ Version Timeline

| Year | Standard | Conventional Name | Notes |
|------|----------|-------------------|-------|
| 2011 | ISO/IEC 14882:2011 | **C++11** | Massive update — new baseline |
| 2014 | ISO/IEC 14882:2014 | **C++14** | Minor improvements |
| 2017 | ISO/IEC 14882:2017 | **C++17** | Many useful additions |
| 2020 | ISO/IEC 14882:2020 | **C++20** | Concepts, ranges, coroutines |
| 2024 | ISO/IEC 14882:2024 | **C++23** | Latest finalized standard |
| TBD  | TBD | **C++26** | In development |

> ✅ **Recommendation:** For learning, use the **latest standard your compiler supports**.
> In professional settings, one or two versions behind latest is common.

### How to Set Language Standard

| IDE / Compiler | How |
|----------------|-----|
| Visual Studio | Project Properties > C/C++ > Language > C++ Language Standard: `ISO C++ Latest (/std:c++latest)` |
| Code::Blocks | Settings > Compiler > check the latest `Have g++ follow C++XX standard` |
| GCC / Clang | Add `-std=c++17` (or `c++20`, `c++23`) to compile command |
| VS Code | Add `"-std=c++20"` (or preferred) in `tasks.json` args |

> ⚠️ Visual Studio requires setting language standard **per project** — set it every time you create a new project (or save as a template).

---

## 0.13 — Checking Your Language Standard

Run this program to see which C++ standard your compiler is currently using:

```cpp
#include <iostream>

const int numStandards = 7;
const long stdCode[numStandards] = { 199711L, 201103L, 201402L, 201703L, 202002L, 202302L, 202612L};
const char* stdName[numStandards] = { "Pre-C++11", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26" };

long getCPPStandard()
{
#if defined (_MSVC_LANG)
    return _MSVC_LANG;
#elif defined (_MSC_VER)
    return -1;
#else
    return __cplusplus;
#endif
}

int main()
{
    long standard = getCPPStandard();

    if (standard == -1)
    {
        std::cout << "Error: Unable to determine your language standard.\n";
        return 0;
    }

    for (int i = 0; i < numStandards; ++i)
    {
        if (standard == stdCode[i])
        {
            std::cout << "Your compiler is using " << stdName[i]
                << " (language standard code " << standard << "L)\n";
            break;
        }
        if (standard < stdCode[i])
        {
            std::cout << "Your compiler is using a preview/pre-release of " << stdName[i]
                << " (language standard code " << standard << "L)\n";
            break;
        }
    }

    return 0;
}
```

---

## ✅ Chapter 0 — Quick Setup Checklist

Before writing your first real C++ programs, ensure:

- [ ] IDE installed (Visual Studio / Code::Blocks / VS Code)
- [ ] C++ compiler supports at least C++17
- [ ] Language standard set to latest available
- [ ] Compiler extensions **disabled** (`/permissive-` or `-pedantic-errors`)
- [ ] Warning level set to max (`/W4` or `-Wall -Wextra`)
- [ ] Treat warnings as errors enabled (`/WX` or `-Werror`)
- [ ] Using **debug build** during development
- [ ] First project created as **console application**
- [ ] Primary file named `main.cpp`

---

## 🔑 Key Terminology Reference

| Term | Meaning |
|------|---------|
| **Source code** | Human-written C++ instructions in `.cpp` files |
| **Object file** | Compiled machine code output per `.cpp` file (`.o` / `.obj`) |
| **Executable** | Final runnable program produced by the linker |
| **Compiler** | Translates C++ source → object files |
| **Linker** | Combines object files + libraries → executable |
| **IDE** | Integrated Development Environment — editor + compiler + debugger in one |
| **Build** | Full process: compile all files + link → executable |
| **Debug config** | Build mode for development — no optimizations, includes debug symbols |
| **Release config** | Build mode for shipping — optimized, no debug symbols |
| **Compiler extensions** | Non-standard behaviors added by specific compilers — should be disabled |
| **Diagnostic** | Compiler message about an issue (error = halt, warning = continue) |
| **Portable** | Program that runs on multiple platforms without modification |
| **Standard library** | Built-in C++ library — `iostream`, `string`, `vector`, etc. |

---

*Notes generated from learncpp.com — Chapter 0 (lessons 0.1–0.13)*