# 12_references_pointers

This chapter explains how references and pointers work in C++, focusing on their differences, use cases, and best practices.

## Key Concepts
- **References** are aliases for existing variables, declared with `&`, and must be initialized.
- **Pointers** store memory addresses, declared with `*`, and can be null or uninitialized.
- **Pointer Arithmetic** allows operations like incrementing or decrementing pointers, which is not allowed with references.
- **Dereferencing** uses `*` to access the value at a pointer's address, while references access values directly.
- **nullptr** is the preferred way to represent a null pointer, avoiding C-style `NULL`.
- **Smart Pointers** like `unique_ptr` and `shared_ptr` manage memory automatically, reducing leaks.
- **Pointer to Member** allows accessing members of a class through a pointer.
- **Reference to Member** is a reference to a specific member of a class.
- **Overloading** can be done with references to avoid unnecessary copies.
- **Const Correctness** ensures that const objects can only be accessed through const references or pointers.

## Critical Insights
### Why References Are Better Than Pointers For Parameters
```cpp
void func(int& x) { x = 10; }
void func(int* x) { if (x) *x = 10; }
```
References are safer and cleaner for function parameters as they cannot be null and avoid the need for null checks.

### Why Dereferencing a Null Pointer Is Undefined Behavior
```cpp
int* p = nullptr;
int x = *p; // Undefined behavior
```
Dereferencing a null pointer leads to undefined behavior, which can cause crashes or other unpredictable results.

## What to Remember
⚠️ Always initialize pointers to avoid dangling references and undefined behavior.  
⚠️ Use references when you want to avoid copying objects and ensure safety.  
⚠️ Prefer `nullptr` over `NULL` for better type safety and clarity.