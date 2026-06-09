// ── WHY CONVERSION IS NEEDED ────────────────────────────────
// int 3    → bits: 0000 0000 0000 0000 0000 0000 0000 0011
// float 3.0 → bits: 0100 0000 0100 0000 0000 0000 0000 0000
// Same "3", completely different bit layout.
// Compiler can't just copy int bits into float memory —
// it would produce garbage. It must CONVERT the value.


// ── [NEW] memcpy TRICK — what happens if you DON'T convert ──
// This is the "what if the compiler just copied bits" demo.
// Not something you'll use in production, but good to know
// what memcpy does and why it lives in <cstring>.

#include <iostream>
#include <cstring>   // memcpy lives here — copies raw bytes between memory

int main()
{
    int n { 3 };
    float f {};

    // memcpy(destination, source, num_bytes)
    // Copies raw bits of n directly into f — NO conversion
    std::memcpy(&f, &n, sizeof(float));

    std::cout << f << '\n';  // Output: 4.2039e-45  (garbage — expected)

    return 0;
}
// Takeaway: int 3's bits, when read as float, mean something completely different.
// This is exactly WHY the compiler converts instead of just copying.


// ── WHEN IMPLICIT CONVERSION HAPPENS ────────────────────────
// Compiler silently converts whenever types mismatch in these contexts:

// 1. Initialization / assignment
double d { 3 };    // int → double
d = 6;             // int → double

// 2. Return value mismatch
float doSomething() { return 3.0; }  // double → float

// 3. Binary operators with mixed types
double result { 4.0 / 3 };  // int 3 → double

// 4. Non-bool in if-statement
if (5) {}  // int → bool (0 = false, anything else = true)

// 5. Function argument mismatch
void foo(long l) {}
foo(3);  // int → long


// ── STANDARD CONVERSION CATEGORIES (just the map) ───────────
// Don't memorize all 14. Know the 2 that matter most:
//
//  ✅ Numeric PROMOTIONS  → small type upgraded to int/double (safe, no data loss)
//
//  ✅ Numeric CONVERSIONS → everything else (can lose data)
//
//
//  Others you'll meet later:
//  • Qualification conversions  → adds/removes const
//  • Value transformations      → lvalue/rvalue stuff (ch.12)
//  • Pointer conversions        → nullptr, void*, base class (later chapters)


// ── WHEN CONVERSION FAILS ───────────────────────────────────

// Case 1: No known conversion path
// int x { "14" };  // ❌ const char* → int doesn't exist → compile error

// Case 2: Brace-init blocks narrowing conversions (data loss)
// int x { 3.5 };   // ❌ double → int loses .5 → compile error
int x ( 3.5 );      // ✅ old-style () allows it (but value becomes 3, lossy)
int y = 3.5;        // ✅ = also allows it (same lossy result)
// Rule: {} is the strictest form of initialization. Prefer it for safety.