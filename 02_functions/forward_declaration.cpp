#include <iostream>
 
 
// ── WHY FORWARD DECLARATIONS EXIST ───────────────────────────────────────────
//
// The compiler processes source files sequentially, top to bottom.
// If you call a function before it has been defined, the compiler has no
// information about it: what parameters does it take? What does it return?
// It cannot validate your call, so it refuses to compile.
//
// ❌ Without a forward declaration (and add() defined below main):
//   int main() {
//       std::cout << add(3, 4);   // COMPILE ERROR: 'add' was not declared in this scope
//   }
//   int add(int x, int y) { return x + y; }  // too late, compiler already failed
//
// ✅ Solution 1, reorder: define add() ABOVE main()
// ✅ Solution 2, forward declaration: tell the compiler add() exists first
 
 
// ── FORWARD DECLARATION SYNTAX ───────────────────────────────────────────────
//
// A declaration tells the compiler: type, name, and parameter types.
// A definition provides: all of the above PLUS the function body.
//
// The parameter NAMES are optional in a declaration, only types are required.
// The names are helpful for documentation but carry no compiler meaning.
 
int add(int x, int y);  // ✅ forward declaration with names (preferred for readability)
// int add(int, int);   // ✅ also valid, names omitted
// Both say the same thing to the compiler: "add takes two ints, returns an int"
 
 
// ── NOW main() CAN USE add() ─────────────────────────────────────────────────
//
// The compiler has seen the declaration above. When it reaches the call below,
// it knows add() exists and has the right signature. It trusts that the linker
// will find the actual definition later.
 
int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    // ✅ works because we forward declared add() above
    // The compiler generates a call instruction; the linker resolves where add() lives.
 
    return 0;
}
 
 
// ── THE ACTUAL DEFINITION (can be anywhere after the declaration) ─────────────
//
// The linker (not the compiler) is responsible for finding this definition
// and connecting it to the call site in main(). The compiler only needs the
// declaration to validate the call.
 
int add(int x, int y)
{
    return x + y;
}
 
 
// ── THREE SCENARIOS WHERE REORDERING IS IMPOSSIBLE ───────────────────────────
//
// Scenario 1: Functions in separate files
//   main.cpp calls add() but add() is defined in math.cpp.
//   You CANNOT reorder across files. Forward declaration in a header is required.
//
// Scenario 2: Circular dependencies
//   foo() calls bar(), and bar() calls foo().
//   No ordering satisfies both, one must be declared before the other is defined.
//   Forward declarations break the circular dependency:
//
//   int bar(int);       // declare bar first
//   int foo(int x) { return bar(x + 1); }   // can now use bar
//   int bar(int x) { return foo(x - 1); }   // can now use foo (already declared)
//
// Scenario 3: Large projects with hundreds of files
//   Reordering is not a scalable strategy. Header files containing declarations
//   are the systematic solution. (Chapter 2.11)
 
 
// ── DECLARATION vs DEFINITION, THE RULE ─────────────────────────────────────
//
// A function can be DECLARED multiple times (as long as signatures match).
// A function can be DEFINED only ONCE across the entire program.
//   → Declaring twice: fine
//   → Defining twice: linker error ("multiple definition of...")
//
// This is the "One Definition Rule" (ODR), one of C++'s most important rules.
// You'll encounter it again in Chapter 7 when studying linkage.
 