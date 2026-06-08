// ============================================================
//  CHAPTER 11 — DEFAULT ARGUMENTS  (11.5)
// ============================================================

#include <iostream>
#include <string_view>

// ─────────────────────────────────────────────────────────────
//  WHAT ARE DEFAULT ARGUMENTS?
// ─────────────────────────────────────────────────────────────
// A default argument is a fallback value the compiler uses when the
// caller doesn't supply that argument. The compiler literally rewrites
// the call at compile time — e.g. print(3) becomes print(3, 4).

void print(int x, int y = 4)           // y defaults to 4
{
    std::cout << "x=" << x << " y=" << y << '\n';
}
// print(1, 2)  →  x=1  y=2   (caller-supplied)
// print(3)     →  x=3  y=4   (default used)

// Only = syntax works. Parentheses and braces are compile errors:
//   void foo(int x = 5);    ✔
//   void foo(int x ( 5 ));  ✗
//   void foo(int x { 5 });  ✗


// ─────────────────────────────────────────────────────────────
//  RULES
// ─────────────────────────────────────────────────────────────
// 1. Every parameter to the RIGHT of a defaulted one must also be defaulted.
//    void bad(int x = 1, int y);    // compile error
//    void ok (int x, int y = 1);    // fine

// 2. Arguments must be supplied LEFT to RIGHT — you cannot skip.
//    void f(int a = 1, int b = 2, int c = 3);
//    f(10, 20, 30)  →  ok
//    f(10, 20)      →  ok  (c = 3)
//    f(10)          →  ok  (b = 2, c = 3)
//    f()            →  ok  (a=1, b=2, c=3)
//    f(,,30)        →  NOT valid C++ syntax

// 3. Cannot redeclare a default argument in the same translation unit.
//    If there's a forward declaration, put the default THERE (not in definition).

void multiDefault(int x = 10, int y = 20, int z = 30)
{
    std::cout << x << ' ' << y << ' ' << z << '\n';
}
// multiDefault(1,2,3) → 1 2 3
// multiDefault(1,2)   → 1 2 30
// multiDefault(1)     → 1 20 30
// multiDefault()      → 10 20 30


// ─────────────────────────────────────────────────────────────
//  WHERE TO DECLARE THE DEFAULT — FORWARD DECLARATION PATTERN
// ─────────────────────────────────────────────────────────────
// If function is declared in a header, put default there. Definition has none.
//
// foo.h:
//   void printVal(int x, int y = 4);   ← default here
//
// foo.cpp:
//   void printVal(int x, int y)        ← no default (already declared)
//   { ... }
//
// This matters because the compiler must see the default BEFORE the call site.

void forward_declared(int x, int y = 99);   // default declared here
void forward_declared(int x, int y)         // NOT redeclared here — that's an error
{
    std::cout << x << ' ' << y << '\n';
}


// ─────────────────────────────────────────────────────────────
//  DEFAULT ARGUMENTS + OVERLOADING
// ─────────────────────────────────────────────────────────────
// Default args are NOT part of a function's signature (type signature).
// So these three are three distinct overloads:
//   void print(int x);
//   void print(int x, int y = 10);       signature = print(int, int)
//   void print(int x, double y = 20.5);  signature = print(int, double)
//
// But defaults can cause AMBIGUOUS MATCHES:

void ambig(int x = 0)    {}
void ambig(double d = 0.0) {}
// ambig();   → AMBIGUOUS — compiler can't decide between ambig(0) or ambig(0.0)

// Trickier example:
//   void print(int x);                   // A
//   void print(int x, int y = 10);       // B
//   void print(int x, double y = 20.5);  // C
//
//   print(1, 2);   → B (exact)
//   print(1, 2.5); → C (exact)
//   print(1);      → AMBIGUOUS: matches A, B, or C


// ─────────────────────────────────────────────────────────────
//  WHEN TO USE DEFAULT ARGUMENTS
// ─────────────────────────────────────────────────────────────
// Use when:
//   • A parameter has a "most common" value but callers might want to override.
//   • You're adding a new parameter to an existing function without breaking
//     all existing call sites (add it with a default → old calls still compile).
//
// Good examples:
//   int  rollDie(int sides = 6);
//   void openLog(std::string filename = "default.log");
//
// Put the most-likely-to-be-overridden parameter LEFTMOST.


int main()
{
    print(1, 2);            // 1 2  (both explicit)
    print(3);               // 3 4  (default y)

    multiDefault(1, 2, 3);  // 1 2 3
    multiDefault(1, 2);     // 1 2 30
    multiDefault(1);        // 1 20 30
    multiDefault();         // 10 20 30

    forward_declared(5);    // 5 99 (uses declared default)

    return 0;
}