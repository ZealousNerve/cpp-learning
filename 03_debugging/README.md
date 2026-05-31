# 03_debugging

## Key Concepts  
- **Debugging strategies**: Reproducing errors, commenting out code, validating code flow with `std::cerr`, and using preprocessor directives to manage debug statements.  
- **Logging tools**: Using `std::clog` and third-party libraries like **plog** for unbuffered, timestamped logs.  
- **Integrated debugger commands**: `step into`, `step over`, `step out`, `run to cursor`, `continue`, breakpoints, and the call stack.  
- **Debug output best practices**: Prioritize `std::cerr` over `std::cout` for immediate feedback during debugging.  

## Critical Insights  
```cpp
// ❌ std::cout is buffered; errors may not appear immediately  
std::cout << "Debug message";  

// ✅ Use std::cerr for unbuffered, immediate output  
std::cerr << "Debug message" << std::endl;  
```  

```cpp
// ❌ Debug statements clutter code; use preprocessor directives  
std::cerr << "Value of x: " << x << std::endl;  

// ✅ Enable/disable debug statements with #ifdef  
#ifdef DEBUG_ENABLE  
std::cerr << "Value of x: " << x << std::endl;  
#endif  
```  

```cpp
// ✅ Plog example: Log to file with timestamp and severity  
#include <plog/Log.h>  
plog::init(plog::debug, "Logfile.txt");  
PLOGD << "main() called";  
```  

## Files in this Chapter  
| File | What it demonstrates |  
|------|----------------------|  
| `debugging_strategy.cpp` | Debugging tactics, logging with plog, and debug output best practices |  
| `Integrated_debugger.cpp` | Debugger commands (step into/over, breakpoints, call stack) and logging setup |  

## What to Remember  
- ❌ **Never rely on `std::cout` for critical debug output**—use `std::cerr` or a logger.  
- ❌ **Forgetting to flush buffers** can hide errors; enable `std::unitbuf` for `std::cout` temporarily.  
- ❌ **Misusing debugger commands** (e.g., `step over` vs `step into`) can lead to missed bugs.