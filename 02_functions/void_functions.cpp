#include <iostream>
 
 
// ── WHAT void MEANS ──────────────────────────────────────────────────────────
//
// void in the return type position is not "empty", it is an explicit promise
// to the caller: "I will not give you back a value."
// The function performs a task (a side effect) and then control returns.
//
// Contrast with value-returning functions:
//   int  add(int x, int y) → produces a value the caller can use
//   void printHi()         → produces no value; caller cannot use its "result"
 
 
// ── EARLY RETURN IN A VOID FUNCTION ──────────────────────────────────────────
//
// A void function can use a bare `return;` (no value) to exit early.
// This is useful for guard clauses, bailing out when a precondition fails.
//
// The return at the END of a void function is completely optional.
// The compiler inserts it automatically. Most style guides omit it.
 
void printHi()
{
    std::cout << "Hi" << '\n';
 
    return;     // optional, redundant here, but legal
                // control returns to caller at this point
}               // implicit return also here if the above is removed
 
 
// ── GUARD CLAUSE PATTERN (early return) ──────────────────────────────────────
//
// Early returns are the idiomatic way to handle error/invalid cases
// in void functions without nesting the entire function body in an if block.
 
void printPositive(int x)
{
    if (x <= 0)
        return;     // ✅ exit early, don't print anything for non-positive values
 
    std::cout << x << " is positive\n";
    // deeper logic continues here, one level of indentation, uncluttered
}
 
 
// ── THE COMPILE ERROR CASE ───────────────────────────────────────────────────
//
// void functions return nothing. Using their "result" is a compile-time error.
// The compiler will refuse to build, this is never a silent runtime problem.
 
void doSomething()
{
    std::cout << "doing something\n";
}
 
// void demonstrate_error()
// {
//     std::cout << doSomething();   // ❌ COMPILE ERROR
//     //                               error: void value not ignored as it ought to be
//     //                               (GCC message)
//     //
//     // The function returns nothing, there is literally nothing to print.
//     // The compiler catches this before the program is ever built.
// }
 
 
// ── RETURN TYPE void IS NOT THE SAME AS NO RETURN TYPE ───────────────────────
//
// In C++ (unlike C), omitting the return type is illegal.
// Every function must explicitly declare what it returns.
//
//   doThing() { }        // ❌ ILLEGAL in C++, return type required
//   void doThing() { }   // ✅ correct
 
 
int main()
{
    printHi();              // ✅ call is fine, we just don't use a return value
    // std::cout << printHi(); // ❌ compile error, void has no value to print
 
    printPositive(5);       // prints "5 is positive"
    printPositive(-3);      // prints nothing, early return triggered
 
    doSomething();          // fine, side effect happens, no value used
 
    return 0;
}