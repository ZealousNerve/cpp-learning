#include <iostream>
 
// ── Destruction order is LIFO ────────────────────────────────────────────────
// When add() returns, y is destroyed BEFORE x, even though x was created first.
// This mirrors a stack, last in, first out.
 
int add(int x, int y)   // x and y created here (enter scope)
{
    return x + y;
}   // y destroyed first, then x, reverse of creation order
 
int main()
{
    int a { 5 };    // created, enters scope
    int b { 6 };    // created, enters scope
 
    std::cout << add(a, b) << '\n';
 
    return 0;
}   // b destroyed first, then a, reverse of declaration order
 
// ── Temporary objects have no scope ─────────────────────────────────────────
// The return value of add() is a temporary object (an rvalue).
// Temporaries have no name, no scope, and live only long enough to
// be used in the expression they appear in.
 
// ── Best practice: define variables close to first use ──────────────────────
// In modern C++, do NOT declare all variables at the top of the function
// (C89 style). Declare them at the point they are first needed.
// This reduces the chance of using an uninitialized variable by accident.
