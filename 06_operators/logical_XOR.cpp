#include <iostream>
int main () {
    // ── THE PROBLEM ─────────────────────────────────────────────
    // C++ has NO built-in logical XOR operator.
    // ^ exists but it is BITWISE XOR — works bit-by-bit on integers.
    // So this is WRONG for logical use:

    int a = 5, b = 3;
    a ^ b;  // 0101 ^ 0011 = 0110 = 6  ← not true/false, just bits


    // ── KEY INSIGHT ─────────────────────────────────────────────
    // On booleans, (!=) behaves exactly like logical XOR.
    // Because XOR means "are these two different?"
    // And != means "are these two different?" — same thing!
    //
    //   true  != true   → false   (same → not XOR)
    //   true  != false  → true    (different → XOR!)
    //   false != true   → true    (different → XOR!)
    //   false != false  → false   (same → not XOR)
    //
    // So the plan is: convert operands to bool first, then use !=


    // ── METHOD 1 : static_cast<bool> ────────────────────────────
    // Explicitly converts any type to bool, then compares with !=
    // Verbose but crystal clear. Use this in real/production code.

    int x = 5, y = 0;

    if (static_cast<bool>(x) != static_cast<bool>(y))
    {
        // 5 → true, 0 → false, true != false → true ✓
    }

    // 3 operands — evaluates LEFT TO RIGHT: (x XOR y) XOR z
    if (static_cast<bool>(x) != static_cast<bool>(y) != static_cast<bool>(z))
    {
        // true when ODD number of operands are non-zero
    }


    // ── METHOD 2 : double-bang !! ────────────────────────────────
    // !! is a trick to convert any value to its bool equivalent.
    // Shorter than static_cast. Add a comment — it's not obvious.

    if (!!x != !!y) { }          // x XOR y
    if (!!x != !!y != !!z) { }   // x XOR y XOR z

    // How !! works, step by step (x = 5):
    //   x   = 5
    //   !x  →  false   // "is 5 falsy?" no → true, then NOT → false
    //   !!x →  true    // NOT false → true (back to logical meaning of x)
    //
    // Why TWO bangs, not one?
    //   Single ! converts to bool BUT also INVERTS the value.
    //   For odd number of operands, that inversion flips the final result.
    //   Second ! flips it back — so you get clean bool, correct value.


    // ── 3-OPERAND TRACE ─────────────────────────────────────────
    // != is left-associative so:
    //   !!a != !!b != !!c  ==  (!!a != !!b) != !!c

    // Example: a=1, b=1, c=1  → odd count of truths → XOR = true
    //   !!a=T, !!b=T → (T != T) = F
    //   F, !!c=T     → (F != T) = T  ✓

    // Example: a=1, b=1, c=0  → even count → XOR = false
    //   !!a=T, !!b=T → (T != T) = F
    //   F, !!c=F     → (F != F) = F  ✓


    // ── QUICK REFERENCE ─────────────────────────────────────────
    //
    //  a ^ b                             ❌  bitwise, not logical
    //  static_cast<bool>(a) != ...       ✅  verbose, readable, use in prod
    //  !!a != !!b                        ✅  concise, only with a comment
    //
    // Rule: use static_cast<bool> by default.
    //       use !! only if you've left a comment explaining it.

    return 0;
}