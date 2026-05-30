# C++ Forward Declarations, Headers, Preprocessor & Functions — Quick Reference

## Forward Declarations
- Compiler reads **top-to-bottom, one pass only** — calling a function before it's defined = compile error
- A **forward declaration** tells the compiler the function's signature without the body
- Parameter names are optional in declarations, only types are required
```cpp
  int add(int x, int y);  // declaration
  int add(int, int);      // also valid
```
- The **linker** (not compiler) finds the actual definition later
- Use when: functions are in separate files, circular dependencies exist, or project is too large to reorder

## One Definition Rule (ODR)
- A function can be **declared** multiple times (signatures must match)
- A function can be **defined only once** across the entire program
- Defining twice = linker error: `"multiple definition of..."`

---

## Header Files
- Each `.cpp` file is compiled **in complete isolation** — headers share declarations across files
- `#include` is a **copy-paste operation** — pastes the entire header content at that point
- **Angle brackets** `<iostream>` → system/library headers
- **Quotes** `"myHeader.h"` → your own project headers

### What belongs in headers ✅
- Function declarations, class declarations, type definitions, `constexpr`/`inline` variables, template definitions

### What does NOT belong in headers ❌
- Function/variable **definitions** (causes ODR violation when included in multiple files)
- `#include`-ing `.cpp` files
- Relative paths like `"../utils/helper.h"`

### Standard Library Header Naming
- C++ stdlib: no extension → `#include <iostream>`, `#include <vector>`
- C stdlib in C++: `c` prefix → `#include <cmath>`, `#include <cstdlib>`
- Your own headers: use `.h` → `mymath.h`, `player.h`

---

## Header Guards
Header guards prevent a header file from being included more than once in the same translation unit (which would cause redefinition errors).

```cpp
// add.h
#ifndef ADD_H       // "if ADD_H is not defined yet..."
#define ADD_H       // "...define it now (so next time this block is skipped)"

int add(int x, int y);   // your declarations go here

#endif              // end of the guard
```
- The name (`ADD_H`) is conventionally the **filename in ALL_CAPS with `.` replaced by `_`**
- Modern alternative: `#pragma once` (not standard but supported by all major compilers)
```cpp
  #pragma once
  int add(int x, int y);
```
- Without header guards, including the same header twice = compiler sees the declaration twice → error

---

## The Preprocessor
- Runs **before** the compiler — pure text substitution, zero C++ awareness
- Pipeline: `Source → [Preprocessor] → Translation Unit → [Compiler] → Object File → [Linker] → Executable`
- Directives start with `#`, end at newline (no semicolon)
- To see preprocessor output: `g++ -E yourfile.cpp`

---

## Macros (`#define`)
```cpp
#define MAX 30          // object-like macro — replaced with 30 everywhere
#define DOUBLE(x) (x)+(x)  // function-like macro — dangerous!
```
- No type, no scope, not debuggable — **prefer `constexpr` in modern C++**
- Macros don't respect function/class/namespace boundaries

### Conditional Compilation
```cpp
#define PRINT_JOE

#ifdef PRINT_JOE   // compiles if PRINT_JOE is defined
    ...
#endif

#ifndef PRINT_BOB  // compiles if PRINT_BOB is NOT defined
    ...
#endif

#if 0              // best way to comment out multi-line blocks (handles nested comments)
    ...
#endif
```

---

## Void Functions
- `void` = explicit promise: "I return no value"
- Using a void function's result in an expression = **compile error** (caught immediately, never runtime)
- `return;` (bare) is legal for early exit — use for guard clauses
- Trailing `return;` at end of void function is optional
```cpp
void printPositive(int x) {
    if (x <= 0) return;   // guard clause — early exit
    std::cout << x << " is positive\n";
}
```

---

## Local Scope & Variable Lifetime
- **Scope** = where an identifier is *visible* (compile-time)
- **Lifetime** = when an object *exists in memory* (runtime)
- Variables destroyed in **reverse order of creation (LIFO)**
- Define variables **close to first use** (not all at top — that's C89 style)
- Temporary/return values have no scope; they live only for the expression they appear in