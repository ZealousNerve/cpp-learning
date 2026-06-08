# 07_scope_linkage

This chapter explores how variables are scoped and linked within programs, focusing on duration, shadowing, and linkage rules.

## Key Concepts
- **Scope** defines where a variable can be accessed, such as local, global, or nested blocks.
- **Linkage** determines how variables are connected across translation units, with internal and external linkage.
- **Static duration** means variables are created at program start and destroyed at end, like global and static local variables.
- **Automatic duration** variables are created and destroyed with their block, such as local variables and function parameters.
- **Shadowing** occurs when a nested variable hides an outer variable with the same name.
- **Variable initialization** includes zero-initialization, value initialization, and list initialization.
- **Const static local variables** allow expensive initialization to occur once, improving performance.
- **Global variables** are defined in the global namespace and have static duration.
- **Namespace resolution** uses the scope resolution operator to access global variables within local scopes.
- **Variable lifetime** is determined by its duration, affecting memory management and program behavior.

## Critical Insights
### Internal vs. External Linkage
```cpp
// internal linkage
static int g_x;

// external linkage
int g_y;
```
Internal linkage restricts variable access to the translation unit, while external linkage allows access across translation units. This distinction is crucial for managing variable visibility and avoiding name collisions.

### Static Local Variables
```cpp
#include <iostream>
int counter = 0;
void increment() {
    static int count = 0;
    count++;
    std::cout << count << std::endl;
}
int main() {
    increment(); // 1
    increment(); // 2
    return 0;
}
```
Static local variables retain their value between function calls, making them useful for maintaining state without global variables. They are initialized only once, improving efficiency.

## What to Remember
⚠️ Avoid shadowing global variables with local variables of the same name to prevent unintended behavior.  
⚠️ Use `static` for local variables that need to retain values between function calls.  
⚠️ Understand the difference between internal and external linkage to manage variable visibility correctly.