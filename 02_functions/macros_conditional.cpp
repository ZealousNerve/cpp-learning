#include <iostream>
 
 
// ── WHAT A MACRO IS ───────────────────────────────────────────────────────────
//
// A macro is a find-and-replace rule for the preprocessor.
// When the preprocessor sees the identifier, it replaces it with the
// substitution text, BEFORE the compiler ever parses the code.
//
// Two types:
//   Object-like macros:   #define IDENTIFIER substitution_text
//   Function-like macros: #define IDENTIFIER(params) substitution_text
//
// Neither ends with a semicolon (they are directives, not statements).
// Convention: macro names are ALL_CAPS_WITH_UNDERSCORES.
 
 
// ── OBJECT-LIKE MACRO: text substitution ──────────────────────────────────────
//
// ❌ Old way (macro):
#define MAX_STUDENTS 30     // preprocessor replaces MAX_STUDENTS → 30 everywhere
                            // no type, no scope, no debugger visibility
//
// ✅ Modern way (constexpr):
// constexpr int MAX_STUDENTS { 30 };   // has a type, respects scope, debuggable
 
 
// ── WHY MACROS ARE DANGEROUS ──────────────────────────────────────────────────
//
// #define DOUBLE(x) x + x         // looks like it doubles x
// int result = DOUBLE(3) * 10;    // you'd expect 60
// After substitution: 3 + 3 * 10  // operator precedence: 3 + 30 = 33 ❌
//
// Fix (still bad, use inline functions instead):
// #define DOUBLE(x) ((x) + (x))   // wrapping each operand and the whole expression
//
// The rule: avoid macros with substitution text unless there is genuinely no
// alternative. In modern C++17, there almost always is.
 
 
// ── CONDITIONAL COMPILATION: #ifdef / #ifndef / #endif ────────────────────────
//
// These let you include or exclude code at the preprocessor level.
// The excluded code is removed before the compiler ever sees it,
// it does not appear in the object file at all.
//
// Use case 1: Platform-specific code
//   #ifdef _WIN32
//       // Windows-only code
//   #endif
//
// Use case 2: Debug-only output
//   #ifdef NDEBUG
//       // Release build code
//   #else
//       // Debug build code
//   #endif
//
// Use case 3: Header guards (see header_guards.cpp)
 
#define PRINT_JOE   // defines the identifier PRINT_JOE (no substitution text)
                    // just its existence is enough, #ifdef checks for existence only
 
int demonstrate_ifdef()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n";           // ✅ compiled, PRINT_JOE is defined above
#endif
 
#ifdef PRINT_BOB
    std::cout << "Bob\n";           // ❌ NOT compiled, PRINT_BOB was never #defined
#endif
    //    this entire block is removed before compilation
 
    return 0;
}
 
 
// ── #ifndef, the opposite of #ifdef ──────────────────────────────────────────
//
// #ifndef means "if NOT defined." Compile this block only if the identifier has NOT been #defined yet.
// This is the key mechanism behind header guards (see header_guards.cpp).
 
int demonstrate_ifndef()
{
#ifndef PRINT_BOB
    std::cout << "Bob was not defined, printing this instead\n";  // ✅ compiled
#endif
 
    return 0;
}
 
 
// ── #if 0, the best comment block in C++ ─────────────────────────────────────
//
// Multi-line comments /* ... */ cannot be nested. If you wrap code that
// already contains a comment, the comment ends prematurely and you get errors.
//
// ❌ Problematic:
//   /* comment out this block
//      int x = /* another comment */  5;   ← first /* ends here, breaks the outer */
//   */
//
// ✅ Solution: #if 0 works perfectly with any nested comments or code.
//   #if 0
//       int x = /* another comment */ 5;   // ← fine, entire block is excluded
//       // even single-line comments work
//   #endif
//
// To re-enable the block: change #if 0 to #if 1
 
int demonstrate_if_zero()
{
    std::cout << "This line always runs\n";
 
#if 0
    // Entire block excluded, not compiled, not even parsed
    std::cout << "This line never runs\n";
    std::cout << "Neither does this\n";
    // Even broken C++ would be fine here, it's pure text to the preprocessor
#endif
 
    return 0;
}
 

int main()
{
    // Macro substitution in action:
    // The preprocessor replaces MY_NAME → "Alex" BEFORE the compiler sees this
    // Final compiled code: std::cout << "My name is: " << "Alex" << '\n';
    // The string "My_NAME" literally does not exist in the object file.
#define MY_NAME "Alex"
    std::cout << "My name is: " << MY_NAME << '\n';
 
    demonstrate_ifdef();
    demonstrate_ifndef();
    demonstrate_if_zero();
 
    return 0;
}
 
 
// ── MACRO NAMING RULES ───────────────────────────────────────────────────────
//
// Macro identifiers follow the same rules as C++ identifiers:
//   ✅ letters, numbers, underscores
//   ✅ cannot start with a number
//   ❌ should NOT start with underscore (reserved for compiler/stdlib)
//
// Convention: ALL_CAPS_SNAKE_CASE for macros.
// This visually signals "this is a macro" to any experienced C++ reader.