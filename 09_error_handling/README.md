# 09_error_handling

This chapter explains how to handle errors and invalid input in C++ programs using robust techniques and best practices.

────────────────────────────────────────────────────
## Key Concepts
- **Assertion** is a debugging tool used to check for conditions that should always be true during development.
- **Error handling** involves detecting and responding to errors in a program to prevent crashes and ensure reliability.
- **Input validation** ensures that user input meets expected criteria before processing it further.
- **Stream state flags** indicate the current state of input/output streams, such as whether an error has occurred.
- **Clearing stream errors** restores the stream to a usable state after an error has occurred.
- **Ignoring leftover input** removes invalid or leftover data from the input buffer to prevent unexpected behavior.
- **Robust input patterns** use loops and validation to ensure user input is correct before proceeding.
- **Standard error stream** (`std::cerr`) is used for outputting error messages that can be redirected separately from normal output.
- **EOF handling** ensures the program exits cleanly when the user ends input, rather than entering an infinite loop.
- **Input extraction failure** occurs when the input cannot be converted to the expected type, requiring special handling.

────────────────────────────────────────────────────
## Critical Insights
### ❌ Assertion vs. Error Handling
```cpp
// Assertion (debugging only)
assert(x > 0);

// Error handling (production code)
if (x <= 0) {
    std::cerr << "Invalid input.\n";
    exit(1);
}
```
Assertions are for debugging and are stripped in release builds. Error handling is for production code and ensures the program can recover or exit gracefully.

### ✅ Clearing Stream State Before Ignoring Input
```cpp
if (!std::cin) {
    std::cin.clear();
    ignoreLine();
}
```
Clearing the stream state is essential before ignoring input, as it restores the stream to a usable state and prevents further errors.

### ⚠️ Always Ignore Leftover Input
```cpp
ignoreLine();
```
Ignoring leftover input after successful extraction prevents unexpected behavior and ensures the input buffer is clean for future operations.

────────────────────────────────────────────────────
## What to Remember
⚠️ Always clear stream errors before ignoring leftover input to avoid further issues.  
⚠️ Use `std::cerr` for error messages to ensure they are handled separately from normal output.  
⚠️ Validate all user input to prevent invalid data from causing program failures.