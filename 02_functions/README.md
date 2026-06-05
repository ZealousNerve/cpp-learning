Zombie

# Preprocessor and Void Functions

## Key Concepts
- The preprocessor runs before the compiler and handles `#include`, `#define`, and conditional compilation.
- `#include <header>` inserts the header's content into the source file, while `#include "file"` searches the current directory first.
- `#define` macros are replaced by the preprocessor, which is scope-unaware and active from definition to end of file.
- `void` functions perform side effects and do not return values. Using their result is a compile-time error.
- Early returns in `void` functions are idiomatic for handling invalid cases without deep nesting.

## Critical Insights

```cpp
// ❌ Bad: Using the result of a void function
std::cout << doSomething();  // error: void value not ignored as it ought to be
```

```cpp
// ✅ Good: Early return in a void function
void printPositive(int x) {
    if (x <= 0)
        return;  // exit early without printing
    std::cout << x << " is positive\n";
}
```

```cpp
// ❌ Bad: Missing return type in C++
doThing() { }  // error: return type required
```

```cpp
// ✅ Good: Explicit return type
void doThing() { }  // correct
```

## Files in this Chapter

| File | What it demonstrates |
|------|----------------------|
| macros.cpp | Preprocessor directives, `#define`, and scope issues |
| preprocessor.cpp | How `#include` works and preprocessor output |
| void_functions.cpp | `void` return types, early returns, and common pitfalls |

## What to Remember
- Avoid using the result of a `void` function; it's a compile-time error.
- The preprocessor is scope-unaware, so macros can unintentionally affect large portions of code.
- Always specify a return type for functions in C++; omitting it is illegal.