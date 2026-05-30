# C++ I/O Buffering & Initialization — Quick Reference

## Output Buffering
- `std::cout` appends to a buffer first, then flushes to console
- `std::endl` = `'\n'` **+ flush** (slow in loops)
- `'\n'` = newline only, **no flush** (prefer this)
- `cout` never adds spaces/newlines automatically — you control every character

## Input Buffering (`cin`)
- `cin >>` stops at whitespace, **leaves `'\n'` in buffer**
- **Case 1:** `"5\n"` → reads 5, discards `\n` ✅
- **Case 2:** `"5a\n"` → reads 5, leaves `a\n` in buffer ⚠️ (next read gets `a`)
- **Case 3:** `"b\n"` for an int → **cin enters failed state**, all further reads silently do nothing
  - Fix: `cin.clear()` + `cin.ignore()`
- Before `getline()`, always call `cin.ignore()` to clear leftover `'\n'`

---

## Variable Initialization — 5 Forms

| Form | Syntax | Notes |
|------|--------|-------|
| Default | `int a;` | ❌ **Indeterminate** — undefined behavior to read |
| Copy | `int b = 5;` | Allows silent narrowing |
| Direct | `int c(6);` | Allows silent narrowing |
| **List** | `int d { 7 };` | ✅ **Preferred** — catches narrowing at compile time |
| Value | `int e {};` | Zero-initializes (`0`, `0.0`, `false`, `nullptr`) |

## Key Rules
- **Always use `{}` for new code** — it's the only form that rejects narrowing conversions at compile time
- `int x { 4.5 };` → **compile error** (safe)
- `int x = 4.5;` → compiles silently, `x = 4` (data lost!)
- **Always initialize** — uninitialized variables = undefined behavior