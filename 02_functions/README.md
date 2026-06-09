# 02_functions

Functions are reusable blocks of code that perform specific tasks, enabling modularity and clarity in program design.

────────────────────────────────────────────────────
## Key Concepts
- **void functions** are functions that do not return a value, used for performing actions without producing output.
- **early return** is a pattern where a function exits prematurely to handle invalid cases, improving readability and reducing nesting.
- **guard clauses** are early returns used to handle precondition failures, allowing the rest of the function to focus on valid cases.
- **return type** is the type of value a function returns to its caller, with `void` indicating no value is returned.
- **side effects** are changes made to the state of a program, such as printing to the console or modifying variables.
- **function parameters** are inputs passed to a function, allowing it to operate on different data each time it is called.
- **function calls** are invocations of a function, used to execute its code and potentially use its return value.
- **compile-time errors** are errors detected by the compiler before the program is run, such as using the return value of a `void` function.
- **function declaration** is the syntax used to define a function, including its name, parameters, and return type.
- **function definition** is the implementation of a function, containing the code that performs its task.

────────────────────────────────────────────────────
## Critical Insights
### ❌ Using void functions as if they return a value
```cpp
void doSomething() {
    std::cout << "doing something\n";
}
// std::cout << doSomething(); // ❌ COMPILE ERROR
```
The compiler will catch this error before the program is built, ensuring that developers do not mistakenly use the return value of a `void` function.

### ✅ Early return for error handling
```cpp
void printPositive(int x) {
    if (x <= 0)
        return;     // ✅ exit early, don't print anything for non-positive values
    std::cout << x << " is positive\n";
}
```
Early returns make code more readable by avoiding deep nesting and allowing the function to focus on valid cases.

────────────────────────────────────────────────────
## What to Remember
⚠️ **Avoid using the return value of a void function** — it will result in a compile-time error.
⚠️ **Use early returns for error handling** to keep code clean and focused on valid cases.
⚠️ **Always declare the return type of a function** — omitting it is illegal in C++.