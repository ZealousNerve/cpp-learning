קרוואן: Understanding Scope, Linkage, and Duration in C++

## Key Concepts

- **Scope**: Determines where a name is visible. Local variables have block scope, global variables have file scope, and namespaces allow grouping of related declarations.
- **Linkage**: Determines if multiple declarations of the same name refer to the same entity. Local variables have no linkage, while global variables have external linkage.
- **Duration**: Determines when a variable is created and destroyed. Automatic duration variables are created and destroyed with their block, static duration variables live for the entire program, and dynamic duration variables are managed manually.
- **Shadowing**: A nested variable with the same name as an outer variable hides the outer variable within the nested scope.
- **Namespaces**: Allow grouping of related declarations and prevent name collisions. They can be nested and aliased for convenience.
- **Static Local Variables**: Retain their value between function calls and are initialized only once. Useful for expensive initializations.
- **Inline Variables**: Allow definition of variables in header files without causing multiple definition errors.
- **Linkage Types**: 
  - **No linkage**: Local variables, function parameters.
  - **Internal linkage**: `static` variables within a translation unit.
  - **External linkage**: Global variables, `extern` variables.
- **Namespace Aliases**: Provide shorter names for long namespace paths.

## Critical Insights

### ❌ Local Variables Have No Linkage
```cpp
int main() {
    int x = 5; // local variable with no linkage
    {
        int x = 10; // shadows the outer x
        std::cout << x << '\n'; // prints 10
    }
    std::cout << x << '\n'; // prints 5
    return 0;
}
```

### ✅ Static Local Variables Retain Value
```cpp
#include <iostream>
int expensiveInitialization() {
    static int value = 42; // initialized once
    return value;
}
int main() {
    std::cout << expensiveInitialization() << '\n'; // 42
    std::cout << expensiveInitialization() << '\n'; // 42
    return 0;
}
```

### ❌ Avoid Shadowing
```cpp
int main() {
    int apples = 5;
    {
        int apples = 0;
        apples = 10; // modifies the nested variable
        std::cout << apples << '\n'; // 10
    }
    std::cout << apples << '\n'; // 5
    return 0;
}
```

## Files in this Chapter

| File | What it demonstrates |
|------|----------------------|
| scope.cpp | Demonstrates variable scope, shadowing, and linkage |
| namespace.cpp | Shows how to define and use namespaces, including nested and aliased namespaces |
| variable.cpp | Explains variable duration, static local variables, and global variables |

## What to Remember

- Avoid shadowing variables as it can lead to confusing and hard-to-debug code.
- Use `static` for local variables that need to retain value between function calls.
- Prefer namespaces to organize code and avoid name collisions.