# Changelog, Learning Milestones

> Every significant milestone in this journey. Not just code changes, understanding changes.
> Format: `[Date] -> What I understood for the first time.`

---

## [June 2025] -> Summer Break Begins

**Repository created.** Starting the full LearnCpp.com curriculum from scratch.
Goal: complete all 28 chapters before semester 3 begins.

### Already completed (Semester 2 coursework overlap)
- OOP concepts from Java translated to C++ understanding
- Basic syntax, functions, scope, covered in college OOP course
- Set up Kali Linux on WSL2, ran first `nmap` scans
- JetBrains CLion activated with student license + MinGW

### First genuine C++ insights (not in Java)
- `std::endl` vs `'\n'`, endl flushes the buffer. This is not a style preference, it's a performance choice.
- List-initialization `{}` catches narrowing conversions at compile time. Copy-initialization `=` silently truncates.
- The preprocessor is not C++. It's a text-substitution pass that runs before the compiler ever sees your code.
- `main()` is not always the first thing that runs. Global variable initializers run before it.
- Variables have both *scope* (visibility) and *lifetime* (existence). These are different properties.

---

## [Upcoming milestones to log]

- [ ] First time I understand pointers intuitively (not just syntactically)
- [ ] First time I implement a linked list from scratch
- [ ] First time I write a class with proper RAII
- [ ] First time I use `std::unique_ptr` correctly
- [ ] First time I write a working template function
- [ ] First time I debug a segfault using the call stack
- [ ] First program that links multiple `.cpp` files correctly

---

*This file is a record of understanding, not just code. The commit that fixes a bug matters less than the insight that prevented the next one.*
