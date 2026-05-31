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
<!-- REPO_TREE_START -->
## ◈ Repository Architecture

```
cpp-learning/
│
├── 📄 README.md                   ← You are here
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
│   ├── 📄 debugging_strategy.cpp        ← Include strategy, ::cerr
│   └── 📄 Integrated_debugger.cpp       ← Include different debugging steps
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
<!-- REPO_TREE_END -->

## ◈ Progress Tracker

> Chapters fill in as I complete them. Each `●` is a committed, annotated file.

| Chapter | Topic | Status | Files |
|:-------:|-------|:------:|:-----:|
| Ch.0 | Introduction & Setup | `✅ Done` | 0 |
| Ch.1 | C++ Basics | `✅ Done` | 2 |
| Ch.2 | Functions & Files | `✅ Done` | 8 |
| Ch.3 | Debugging | `✅ Done` | 2 |
| Ch.4 | Fundamental Data Types | `⬜ Upcoming` | 0 |
| Ch.5 | Constants & Strings | `⬜ Upcoming` | 0 |
| Ch.6 | Operators | `⬜ Upcoming` | 0 |
| Ch.7 | Scope, Duration, Linkage | `⬜ Upcoming` | 0 |
| Ch.8 | Control Flow | `⬜ Upcoming` | 0 |
| Ch.9 | Error Detection & Handling | `⬜ Upcoming` | 0 |
| Ch.10 | Type Conversion & Deduction | `⬜ Upcoming` | 0 |
| Ch.11 | Function Overloading & Templates | `⬜ Upcoming` | 0 |
| Ch.12 | References & Pointers | `⬜ Upcoming` | 0 |
| Ch.13 | Enums & Structs | `⬜ Upcoming` | 0 |
| Ch.14 | Introduction to Classes | `⬜ Upcoming` | 0 |
| Ch.15 | More on Classes | `⬜ Upcoming` | 0 |
| Ch.16 | Dynamic Arrays: `std::vector` | `⬜ Upcoming` | 0 |
| Ch.17 | Fixed Arrays: `std::array` | `⬜ Upcoming` | 0 |
| Ch.18 | Iterators & Algorithms | `⬜ Upcoming` | 0 |
| Ch.19 | Dynamic Allocation | `⬜ Upcoming` | 0 |
| Ch.20 | Advanced Functions & Lambdas | `⬜ Upcoming` | 0 |
| Ch.21 | Operator Overloading | `⬜ Upcoming` | 0 |
| Ch.22 | Smart Pointers & Move Semantics | `⬜ Upcoming` | 0 |
| Ch.23 | Object Relationships | `⬜ Upcoming` | 0 |
| Ch.24 | Inheritance | `⬜ Upcoming` | 0 |
| Ch.25 | Virtual Functions & Polymorphism | `⬜ Upcoming` | 0 |
| Ch.26 | Templates & Classes | `⬜ Upcoming` | 0 |
| Ch.27 | Exceptions | `⬜ Upcoming` | 0 |
| Ch.28 | Input & Output Streams | `⬜ Upcoming` | 0 |

---

## ◈ Key Insights So Far

> Summary of Each Chapter

1. [C++ Basics](01_basics/README.md)
2. [Functions](02_functions/README.md)
3. [Debugging](03_debugging/README.md)
4. [DataTypes](04_data_types/README.md)
5. [Constants Strings](05_constants_strings/README.md)
6. [Operators](06_operators/README.md)
7. [Scope Linkage](07_scope_linkage/README.md)
8. [Control Flow](08_control_flow/README.md)
9. [Error Handling](09_error_handling/README.md)
10. [Type System](10_type_system/README.md)
11. [Templates](11_templates/README.md)
12. [Refrence Pointers](12_references_pointers/README.md)
13. [Enums, Struct](13_enums_structs/README.md)
14. [Classes](14_classes/README.md)
15. [More Classes](15_more_classes/README.md)
16. [Vectors](16_vectors/README.md)
17. [Arrays](17_arrays/README.md)
18. [Iterators Algorithm](18_iterators_algorithms/README.md)
19. [Dynamic Allocation](19_dynamic_allocation/README.md)
20. [Advanced Functions](20_advanced_functions/README.md)
21. [Operator Overloading](21_operator_overloading/README.md)
22. [Smart Pointers](22_smart_pointers/README.md)
23. [Object Relationship](23_object_relationships/README.md)
24. [Inheritance](24_inheritance/README.md)
25. [Virtual Functions](25_virtual_functions/README.md)
26. [Templates Classes](26_templates_classes/README.md)
27. [Exceptions](27_exceptions/README.md)
28. [IO Streams](28_io_streams/README.md)



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

---

<div align="center">

**If you're learning C++ too, this repo might help you.**
**If you spot a mistake in my comments, open an issue, I want to know.**

<br/>

`Built with intent. Committed with discipline.`

<br/>

[![GitHub](https://img.shields.io/badge/Follow%20the%20Journey-GitHub-181717?style=flat-square&logo=github)](https://github.com/zealousnerve)

</div>
