# 01_basics

This chapter introduces fundamental C++ concepts like input/output buffering, variable initialization, and string handling.

## Key Concepts
- **Output Buffering**: std::cout appends data to a buffer before sending it to the console, which can be flushed manually or automatically.
- **Input Buffering**: cin stores input in a buffer, and extraction stops at non-matching characters or whitespace, leaving potential leftover data.
- **Newline Responsibility**: std::cout does not add newlines automatically; each line must be explicitly terminated with '\n'.
- **Variable Initialization**: C++ provides multiple initialization forms, including default, copy, direct, and value-initialization.
- **List Initialization**: Braces {} are used for direct-list-initialization, which is preferred for its safety against narrowing conversions.
- **Value-Initialization**: Empty braces {} ensure zero-initialization for fundamental types, guaranteeing a value of 0 or nullptr.
- **Narrowing Conversions**: List-initialization rejects narrowing conversions, while copy and direct initialization silently truncate values.
- **Stream State**: cin enters a failed state on invalid input, requiring explicit reset with cin.clear() and cin.ignore().
- **Buffer Flushing**: std::endl flushes the buffer, which can be inefficient in loops, so '\n' is preferred for performance.
- **Input Handling**: The leftover newline from input can affect subsequent getline() calls, necessitating cin.ignore().

## Critical Insights
### Why std::endl is inefficient in loops
```cpp
std::cout << "line 1" << std::endl;
std::cout << "line 2" << std::endl;
std::cout << "line 3" << std::endl;
```
Using std::endl in a loop causes unnecessary buffer flushes, which can slow down performance. Prefer '\n' for efficiency.

### List-initialization vs. copy-initialization
```cpp
int w1 { 4.5 };  // ❌ COMPILE ERROR, list-init REFUSES narrowing conversions
int w2 = 4.5;    // ✅ compiles, but w2 = 4 (fractional part silently lost)
int w3 (4.5);    // ✅ compiles, but w3 = 4 (fractional part silently lost)
```
List-initialization acts as a compile-time safety net, while copy and direct initialization allow narrowing conversions, which can lead to data loss.

## What to Remember
⚠️ Always flush the buffer explicitly when needed to avoid unnecessary performance overhead.  
⚠️ Use braces {} for variable initialization to prevent narrowing conversions and ensure safety.  
⚠️ Be cautious with leftover newline characters in input buffers, as they can cause unexpected behavior in subsequent input operations.