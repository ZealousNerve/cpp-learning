// ============================================================
// 8.12 — HALTS (Exiting Your Program Early)
// ============================================================

// A HALT = flow control that terminates the program
// In C++, halts are FUNCTIONS, not keywords

// ============================================================
// WHAT HAPPENS ON NORMAL EXIT (when main() returns)
// ============================================================
// 1. Local variables & params are destroyed
// 2. std::exit() is called automatically with main()'s return value
// 3. OS receives the status code

// ============================================================
// std::exit()
// ============================================================
// - Terminates the program NORMALLY
// - "Normal" = expected exit, NOT necessarily successful
// - Cleans up: static storage objects, open files
// - Returns status code to OS
// - Header: <cstdlib>

#include <cstdlib>
#include <iostream>

void cleanup() { std::cout << "cleanup!\n"; }

int main()
{
    std::cout << 1 << '\n';
    cleanup();
    std::exit(0);           // program ends here, status 0 = success
    std::cout << 2 << '\n'; // NEVER executes
    return 0;
}
// Output: 1  cleanup!

// ⚠️ WARNING: std::exit() does NOT destroy local variables
// This can be dangerous if local objects need cleanup (e.g. classes, file handles)

// ============================================================
// std::atexit()
// ============================================================
// - Register a function to auto-call when exit() is triggered
// - Saves you from manually calling cleanup before every exit()
// - Rules: registered function must take no params, return void
// - Multiple registrations = called in REVERSE order (last in, first out)
// - Also triggers when main() returns normally

int main()
{
    std::atexit(cleanup);   // registers cleanup — pass name, NOT cleanup()
    std::cout << 1 << '\n';
    std::exit(0);           // cleanup() auto-called here
    std::cout << 2 << '\n'; // never runs
    return 0;
}
// Output: 1  cleanup!

// ============================================================
// std::abort()
// ============================================================
// - ABNORMAL termination (runtime error, divide by 0, assert fail)
// - Does ZERO cleanup — not local vars, not static, nothing
// - Used internally by assert failures (ch 9)

int main()
{
    std::cout << 1 << '\n';
    std::abort();           // crash-style exit
    std::cout << 2 << '\n'; // never runs
}

// ============================================================
// std::terminate()
// ============================================================
// - Used with exceptions (covered later)
// - Called implicitly when an exception is unhandled
// - By default, calls std::abort()

// ============================================================
// QUICK COMPARISON
// ============================================================
// std::exit()      → normal, cleans static + files, NOT locals
// std::abort()     → abnormal, cleans NOTHING
// std::terminate() → exception-related, calls abort() by default
// std::atexit()    → not a halt, registers auto-cleanup for exit()

// ============================================================
// BEST PRACTICE
// ============================================================
// ❌ Avoid halts — they skip local variable cleanup
// ✅ Prefer exceptions for error handling
// ✅ Use halts ONLY if there's truly no safe way to return from main()

// BONUS TIP: Programs can die unexpectedly (crash, kill, power cut)
// Design your program to handle sudden shutdown gracefully
// e.g. autosave state periodically, flush files often