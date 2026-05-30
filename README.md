<div align="center">

<!-- HERO BANNER -->
```
 ██████╗██████╗ ██████╗       ███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ ██╗   ██╗
██╔════╝██╔══██╗██╔══██╗      ████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗╚██╗ ██╔╝
██║     ██████╔╝██████╔╝      ██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝ ╚████╔╝ 
██║     ██╔═══╝ ██╔═══╝       ██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗  ╚██╔╝  
╚██████╗██║     ██║           ██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║   ██║   
 ╚═════╝╚═╝     ╚═╝           ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝   ╚═╝  
```

**`// Learning C++ the right way, one concept, one file, zero shortcuts`**

<br/>

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=flat-square&logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/17)
[![IDE](https://img.shields.io/badge/IDE-CLion-000000?style=flat-square&logo=clion&logoColor=white)](https://www.jetbrains.com/clion/)
[![Compiler](https://img.shields.io/badge/Compiler-MinGW%20%2F%20GCC-A42E2B?style=flat-square&logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![Reference](https://img.shields.io/badge/Reference-LearnCpp.com-FF6B35?style=flat-square)](https://learncpp.com)
[![Status](https://img.shields.io/badge/Status-Actively%20Learning-brightgreen?style=flat-square)]()
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20WSL2-0078D6?style=flat-square&logo=windows&logoColor=white)]()

<br/>

> *"The expert in anything was once a beginner who refused to give up."*
> 

</div>

---

## ◈ What This Repository Is

This is not a collection of random C++ snippets. This is a **structured, annotated learning journal** built on top of [LearnCpp.com](https://learncpp.com), the gold standard free resource for modern C++.

**The discipline:** After reading each chapter section, I extract only what matters, the non-obvious rules, the gotchas, the "why" behind the "what", and encode it in a single, focused `.cpp` file. Every comment is a learning insight. Every file compiles and runs cleanly.

**The philosophy:**
- One concept per file. No bloat.
- Comments explain *why*, not *what*.
- Standard C++17, no compiler-specific hacks.
- If it feels obvious, it doesn't get committed.

---

## ◈ Repository Architecture

```
cpp-mastery/
│
├── 📄 README.md                   ← You are here
├── 📄 ROADMAP.md                  ← Full LearnCpp.com chapter tracker
├── 📄 CHANGELOG.md                ← Milestone log of the learning journey
├── 📄 .gitignore                  ← Excludes .exe, .obj, IDE noise
│
├── 📁 00_foundations/             ← Ch.0: Toolchain & environment setup
│   ├── 📄 README.md
│   ├── 📄 compiler_notes.md       ← Compiler flags, warnings, standards
│   └── 📄 dev_environment.md      ← CLion + MinGW + WSL2 setup notes
│
├── 📁 01_basics/                  ← Ch.1: Statements, variables, I/O
│   ├── 📄 README.md
│   ├── 📄 io_buffering.cpp        ← cout, cin, endl vs \n, buffer mechanics
│   ├── 📄 variables_init.cpp      ← All 5 init forms + narrowing rules
│   └── 📄 expressions_ops.cpp     ← Literals, operators, expressions
│
├── 📁 02_functions/               ← Ch.2: Functions, scope, preprocessor
│   ├── 📄 README.md
│   ├── 📄 func_basics.cpp         ← main(), status codes, return rules
│   ├── 📄 void_functions.cpp      ← Non-value-returning functions
│   ├── 📄 local_scope.cpp         ← Lifetime, scope, destruction order
│   ├── 📄 forward_declaration.cpp ← Declarations vs definitions
│   ├── 📄 preprocessor.cpp        ← Preprocessing phase deep dive
│   ├── 📄 macros_conditional.cpp  ← Object/function macros, #ifdef, #if 0
│   ├── 📄 header_files.cpp        ← Include mechanics, best practices
│   └── 📄 header_guards.cpp       ← Include guard pattern
│
├── 📁 03_debugging/               ← Ch.3: Debugging mindset & tools
│   ├── 📄 README.md
│   └── 📄 debug_tactics.md        ← Strategies, breakpoints, call stack
│
├── 📁 04_data_types/              ← Ch.4: Fundamental types
│   └── 📄 README.md
│
├── 📁 05_constants_strings/       ← Ch.5: Constants, strings
│   └── 📄 README.md
│
├── 📁 06_operators/               ← Ch.6: Operators & expressions
│   └── 📄 README.md
│
├── 📁 07_scope_linkage/           ← Ch.7: Scope, duration, linkage
│   └── 📄 README.md
│
├── 📁 08_control_flow/            ← Ch.8: if/switch/loops/random
│   └── 📄 README.md
│
├── 📁 09_error_handling/          ← Ch.9: Testing, assert, cin validation
│   └── 📄 README.md
│
├── 📁 10_type_system/             ← Ch.10: Conversions, auto, aliases
│   └── 📄 README.md
│
├── 📁 11_templates/               ← Ch.11: Overloading + function templates
│   └── 📄 README.md
│
├── 📁 12_references_pointers/     ← Ch.12: References, pointers, const
│   └── 📄 README.md
│
├── 📁 13_enums_structs/           ← Ch.13: Enums, structs, class templates
│   └── 📄 README.md
│
├── 📁 14_classes/                 ← Ch.14: OOP - constructors, access
│   └── 📄 README.md
│
├── 📁 15_more_classes/            ← Ch.15: this, static, friends, destructors
│   └── 📄 README.md
│
├── 📁 16_vectors/                 ← Ch.16: std::vector, dynamic arrays
│   └── 📄 README.md
│
├── 📁 17_arrays/                  ← Ch.17: std::array, C-style arrays
│   └── 📄 README.md
│
├── 📁 18_iterators_algorithms/    ← Ch.18: STL iterators & algorithms
│   └── 📄 README.md
│
├── 📁 19_dynamic_allocation/      ← Ch.19: new, delete, heap
│   └── 📄 README.md
│
├── 📁 20_advanced_functions/      ← Ch.20: Lambdas, recursion, stack/heap
│   └── 📄 README.md
│
├── 📁 21_operator_overloading/    ← Ch.21: Operator overloading
│   └── 📄 README.md
│
├── 📁 22_smart_pointers/          ← Ch.22: unique_ptr, shared_ptr, move
│   └── 📄 README.md
│
├── 📁 23_object_relationships/    ← Ch.23: Composition, aggregation
│   └── 📄 README.md
│
├── 📁 24_inheritance/             ← Ch.24: Inheritance in C++
│   └── 📄 README.md
│
├── 📁 25_virtual_functions/       ← Ch.25: Polymorphism, vtables, casting
│   └── 📄 README.md
│
├── 📁 26_templates_classes/       ← Ch.26: Template specialization
│   └── 📄 README.md
│
├── 📁 27_exceptions/              ← Ch.27: Exception handling
│   └── 📄 README.md
│
├── 📁 28_io_streams/              ← Ch.28: File I/O, stream states
│   └── 📄 README.md
│
├── 📁 _notes/                     ← Cross-chapter theory & mental models
│   ├── 📄 theory.md               ← Compiler wisdom, formatting rules
│   ├── 📄 cpp_gotchas.md          ← Traps, UB, and things that surprise
│   └── 📄 mental_models.md        ← How to *think* in C++
│
└── 📁 _sandbox/                   ← Scratch space, not graded
    └── 📄 test.cpp
```

---

## ◈ Progress Tracker

> Chapters fill in as I complete them. Each `●` is a committed, annotated file.

| Chapter | Topic | Status | Files |
|:-------:|-------|:------:|:-----:|
| Ch.0 | Introduction & Setup | `✅ Done` | 2 |
| Ch.1 | C++ Basics | `✅ Done` | 3 |
| Ch.2 | Functions & Files | `✅ Done` | 8 |
| Ch.3 | Debugging | `🔄 In Progress` | 0 |
| Ch.4 | Fundamental Data Types | `⬜ Upcoming` |, |
| Ch.5 | Constants & Strings | `⬜ Upcoming` |, |
| Ch.6 | Operators | `⬜ Upcoming` |, |
| Ch.7 | Scope, Duration, Linkage | `⬜ Upcoming` |, |
| Ch.8 | Control Flow | `⬜ Upcoming` |, |
| Ch.9 | Error Detection & Handling | `⬜ Upcoming` |, |
| Ch.10 | Type Conversion & Deduction | `⬜ Upcoming` |, |
| Ch.11 | Function Overloading & Templates | `⬜ Upcoming` |, |
| Ch.12 | References & Pointers | `⬜ Upcoming` |, |
| Ch.13 | Enums & Structs | `⬜ Upcoming` |, |
| Ch.14 | Introduction to Classes | `⬜ Upcoming` |, |
| Ch.15 | More on Classes | `⬜ Upcoming` |, |
| Ch.16 | Dynamic Arrays: `std::vector` | `⬜ Upcoming` |, |
| Ch.17 | Fixed Arrays: `std::array` | `⬜ Upcoming` |, |
| Ch.18 | Iterators & Algorithms | `⬜ Upcoming` |, |
| Ch.19 | Dynamic Allocation | `⬜ Upcoming` |, |
| Ch.20 | Advanced Functions & Lambdas | `⬜ Upcoming` |, |
| Ch.21 | Operator Overloading | `⬜ Upcoming` |, |
| Ch.22 | Smart Pointers & Move Semantics | `⬜ Upcoming` |, |
| Ch.23 | Object Relationships | `⬜ Upcoming` |, |
| Ch.24 | Inheritance | `⬜ Upcoming` |, |
| Ch.25 | Virtual Functions & Polymorphism | `⬜ Upcoming` |, |
| Ch.26 | Templates & Classes | `⬜ Upcoming` |, |
| Ch.27 | Exceptions | `⬜ Upcoming` |, |
| Ch.28 | Input & Output Streams | `⬜ Upcoming` |, |

---

## ◈ Key Insights So Far

> The things I didn't know I didn't know. Updated every chapter.

<details>
<summary><strong>Ch.1, C++ Basics</strong></summary>

```cpp
// ❌ What most beginners do
int x;          // undefined value, could be 0, could be garbage

// ✅ What C++17 best practice says
int x {};       // value-initialization, always 0 for ints

// 🔥 The trap nobody warns you about
int w1 { 4.5 }; // COMPILE ERROR, list-init catches narrowing conversions
int w2 = 4.5;   // silently loses .5, no warning by default
```

**The endl vs \\n trap:** `std::endl` flushes the output buffer every single call.
In a loop printing 10,000 lines, that's 10,000 unnecessary disk/console flushes.
Use `'\n'` everywhere except when you explicitly need a flush.

**cin's input buffer mechanics:** When you type `5a` and hit enter, `5\n a\n` goes into the buffer.
`cin >> x` extracts `5`, leaves `a\n` in the buffer. Your next `cin` call reads `a` immediately
without waiting for the user. This is the root of most beginner input bugs.

</details>

<details>
<summary><strong>Ch.2, Functions & Files</strong></summary>

```cpp
// The thing about main() most people miss:
// Global variables are initialized BEFORE main() runs.
// If a global's initializer calls a function, that function
// runs before main(). main() is NOT always first.

// Status codes, use the portable way:
#include <cstdlib>
return EXIT_SUCCESS; // more expressive than return 0;
return EXIT_FAILURE; // the only meaningful non-zero value

// Forward declarations enable circular dependency resolution:
int foo(int);  // tell the compiler foo exists
int bar(int x) { return foo(x + 1); }  // can use foo now
int foo(int x) { return x * 2; }       // defined later
```

**The preprocessor is not C++.** It runs as a pure text-substitution pass
before any C++ parsing. `#define`, `#include`, `#ifdef`, none of these
are C++ statements. They have no semicolons. They don't understand types.
Macros don't respect scope. This is why `constexpr` exists to replace `#define`.

**Header files only declare, never define (usually).** Putting a function
*definition* in a header causes "multiple definition" linker errors when
two `.cpp` files include that header. Declarations are fine to include
multiple times, that's exactly what header guards protect against.

</details>

---

## ◈ The File Format Convention

Every `.cpp` file in this repo follows the same structure, making them scannable:

```cpp
/**
 * TOPIC : Local Scope & Variable Lifetime
 * CHAPTER: 2.5, Introduction to local scope
 * SOURCE : https://learncpp.com/cpp-tutorial/introduction-to-local-scope/
 *
 * KEY INSIGHT: Local variables are created at their point of definition
 *              and destroyed in reverse order when they go out of scope.
 *              Destruction order matters, it's LIFO, not FIFO.
 */

// ── CONCEPT 1: Scope vs Lifetime ──────────────────────────────────────────
// Scope = where an identifier can be *seen* (compile-time property)
// Lifetime = when an object *exists* in memory (runtime property)
// They're related but NOT the same thing.

#include <iostream>

int add(int x, int y)   // x, y created here
{
    return x + y;
}   // y destroyed first, then x, reverse order

int main()
{
    int a { 5 };        // created, enters scope
    int b { 6 };        // created, enters scope

    std::cout << add(a, b) << '\n';

    return 0;
}   // b destroyed first, then a, reverse declaration order
    // Best practice: define variables close to first use
```

---

## ◈ My Stack

| Category | Tool | Notes |
|----------|------|-------|
| **Machine** | HP Omen, Ryzen 7 7840HS + RTX 4060 | Compiles fast |
| **OS** | Windows 11 + WSL2 (Kali Linux) | Best of both worlds |
| **IDE** | JetBrains CLion (student license) | Refactoring + debugger |
| **Compiler** | MinGW-w64 (GCC), `-std=c++17 -Wall -Wextra` | Strict warnings on |
| **Reference** | LearnCpp.com (Ch.0 → Ch.28) | The best free C++ resource |
| **Supplementary** | cppreference.com | When I need the spec |
| **Version Control** | Git + GitHub | This repo |

---

## ◈ Build Instructions

All files are standalone, compile any single file directly:

```bash
# Standard compile (any chapter file)
g++ -std=c++17 -Wall -Wextra -o out filename.cpp && ./out

# With sanitizers (recommended for pointer/memory chapters)
g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined -o out filename.cpp && ./out

# CLion: just open the project, CMakeLists.txt handles everything
```

---

## ◈ Why This Exists

I'm a B.Tech CSE student at **IIIT Bhopal**, currently on summer break after semester 2.
I already know Java from my OOP coursework, but C++ has different rules, different pitfalls,
and a completely different mental model around memory.

This repo is my commitment: to spend this summer going deep on C++ the *right* way,
not surface-level syntax familiarity, but genuine understanding of what the machine is doing.

The standard I'm holding myself to: **would this code make a senior SDE at a systems company nod?**

---

## ◈ Roadmap Beyond This Repo

Once this repo is complete (all 28 chapters committed), the plan is:

```
C++ Mastery (this repo)
        │
        ▼
Data Structures & Algorithms in C++
        │
        ├──► Competitive Programming (Codeforces)
        │
        └──► Systems / Security Projects
                    │
                    ├── Network scanner (libpcap)
                    ├── Custom memory allocator
                    └── Toy OS kernel (semester 5-6)
```

---

<div align="center">

**If you're learning C++ too, this repo might help you.**
**If you spot a mistake in my comments, open an issue, I want to know.**

<br/>

`Built with intent. Committed with discipline.`

<br/>

[![GitHub](https://img.shields.io/badge/Follow%20the%20Journey-GitHub-181717?style=flat-square&logo=github)](https://github.com/zealousnerve)

</div>
