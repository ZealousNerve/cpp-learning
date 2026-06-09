# 03_debugging

Debugging is the process of identifying and resolving errors in C++ programs, whether they are syntax or logic-related.

────────────────────────────────────────────────────
## Key Concepts
- **Debugging Strategy**: A methodical approach to isolate and resolve errors by reproducing issues, commenting out code, and validating code flow.
- **std::cerr**: An unbuffered output stream used for immediate error messages during debugging, unlike std::cout which is buffered.
- **Preprocessor Directives**: Conditional compilation tools like #ifdef DEBUG_ENABLE to enable or disable debug statements.
- **Logging with plog**: A third-party library that allows logging to a file, reducing clutter and improving debugging efficiency.
- **Integrated Debugger Commands**: Tools like step into, step over, and continue to control program execution during debugging.
- **Breakpoints**: Markers that pause program execution at specific lines for inspection.
- **Call Stack**: A list of active functions showing the current execution path.
- **Watch Window**: A debugger feature that allows monitoring variable values in real-time.
- **Run to Cursor**: A command to execute the program until it reaches a specific line of code.
- **Log File Output**: Example of logging with plog, showing timestamps and function calls.

────────────────────────────────────────────────────
## Critical Insights
### Why Use std::cerr Over std::cout for Debugging?
```cpp
std::cout << std::unitbuf; // enable automatic flushing for std::cout (for debugging)
```
Using std::cerr ensures immediate output, which is crucial when debugging because it prevents buffering issues that can hide errors.

### How to Initialize and Use plog for Logging
```cpp
plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger
PLOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console
```
plog simplifies logging by allowing you to write to a file, making it easier to track issues without cluttering the console.

────────────────────────────────────────────────────
## What to Remember
⚠️ Always reproduce the error consistently to effectively debug it.  
⚠️ Use preprocessor directives to manage debug statements and keep code clean.  
⚠️ Understand debugger commands like step into, step over, and continue to navigate program flow efficiently.