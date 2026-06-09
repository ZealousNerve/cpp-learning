#include <cassert>   // for assert()
#include <iostream>
#include <cmath>

// ── QUICK CONTEXT ──────────────────────────────────────────
// You already know: if y==0, dividing crashes. You'd normally
// do an if-check. Assertions are a SHORTCUT for that pattern
// specifically for "this should NEVER happen" conditions.

// ── THE BOUNCER PATTERN ────────────────────────────────────
// Best practice: validate at the TOP, return early if bad.
// This keeps nesting low and error + handler code together.

void printDivision(int x, int y)
{
    if (y == 0)             // precondition check — bouncer
    {
        std::cerr << "Error: divide by zero\n";
        return;             // bounce caller out immediately
    }
    std::cout << static_cast<double>(x) / y << "\n";
}

// ── THREE KINDS OF CONDITIONS ──────────────────────────────
// Precondition  → must be true BEFORE a function runs   (y != 0)
// Invariant     → must stay true DURING execution       (loop guard)
// Postcondition → must be true AFTER a function returns (result >= 0)

// ── assert() — RUNTIME ASSERTION ──────────────────────────
// Syntax:  assert(expression);
// If expression == true  → does NOTHING, program continues
// If expression == false → prints message + calls std::abort()
//
// The printed message contains:
//   • the failed expression as text
//   • file name + line number
// That combo pinpoints bugs immediately.

double calcFallTime(double height, double gravity)
{
    assert(gravity > 0.0);  // program ABORTS here if gravity <= 0
                            // much better than a silent wrong result later
    if (height <= 0.0) return 0.0;
    return std::sqrt((2.0 * height) / gravity);
}

// ── MAKING ASSERT MESSAGES DESCRIPTIVE ────────────────────
// Plain:       assert(found);
// Descriptive: assert(found && "Car not found in database");
//
// WHY IT WORKS: a string literal is always `true`
//   found=false → false && true  = false → assert triggers WITH the string
//   found=true  → true  && true  = true  → assert passes silently
// The string shows up in the abort message. Free documentation.

void demoDescriptive(bool found)
{
    assert(found && "Car could not be found in database");
}

// ── NDEBUG — TURNING ASSERTS OFF ──────────────────────────
// In release builds you DON'T want assert overhead.
// When NDEBUG is defined, every assert() becomes a no-op.
//
// IDEs (VS, CLion) auto-define NDEBUG in Release config.
// To disable manually in ONE file (useful for testing):
//
//   #define NDEBUG   ← place BEFORE all #includes to disable
//   #undef  NDEBUG   ← place BEFORE all #includes to force-enable
//
// IMPORTANT RULE: Never put side effects inside assert()
//   assert(++i > 0);  ← BAD: ++i won't run in release build
//   assert(x  > 0);  ← GOOD: x is just read, not modified

// ── static_assert — COMPILE-TIME ASSERTION ────────────────
// Syntax: static_assert(condition, "message");
// Checked by the COMPILER, not at runtime.
// A false condition = compile error, not a crash.
// No header needed — it's a keyword.
// NOT disabled by NDEBUG. Always active.
// Condition MUST be a constant expression (known at compile time).
// Message is optional since C++17.

static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
// ↑ this line runs at compile time, zero runtime cost
// Use this to guard against platform-specific type size surprises

// ── assert vs static_assert — WHEN TO USE WHICH ───────────
// static_assert → anything knowable at compile time
//                 (type sizes, template constraints, constants)
// assert()      → anything that depends on runtime values
//                 (function arguments, user input, file data)
// Prefer static_assert whenever possible (zero runtime cost,
// can't be disabled, catches issues before the program even runs)

// ── assert vs ERROR HANDLING — KEY DIFFERENCE ─────────────
// assert()      → for PROGRAMMING bugs (your fault, should never happen)
//                 compiled OUT in release, no recovery needed
// error handling → for EXPECTED edge cases (user gave bad input, file missing)
//                 stays IN release, program handles gracefully
//
// Sometimes use BOTH:
double getInverse(double x)
{
    assert(x != 0.0);       // catch the bug in dev/debug
    if (x == 0.0)           // handle gracefully in release
        return 0.0;         // (or throw, or return error code)
    return 1.0 / x;
}

// ── ASSERTS FOR UNIMPLEMENTED CASES ───────────────────────
// Document "TODO" cases so they LOUDLY fail instead of silently misbehave:
//   assert(false && "This branch not yet implemented — see issue #42");

int main()
{
    printDivision(10, 2);
    printDivision(10, 0);

    // calcFallTime(100.0, -9.8);  ← uncomment to see assert abort

    std::cout << getInverse(4.0) << "\n";
    std::cout << getInverse(0.0) << "\n";   // hits the if-guard in release
}

// ── SUMMARY ────────────────────────────────────────────────
// assert()        runtime,   debug-only (NDEBUG kills it), no header needed*
// static_assert   compile,   always on,  no header needed,  zero cost
// error handling  runtime,   always on,  recovery possible
//
// Use assert liberally in dev — they are documentation that enforces itself.
// * cassert header IS needed for assert() macro