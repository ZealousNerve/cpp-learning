// ────────────────────────────────────────────────────────────
//  PART 1: THE PROBLEM WITH const
// ────────────────────────────────────────────────────────────

/*
  A const variable with an integral type AND a constant expression
  initializer CAN be used in a constant expression.
  All other const variables CANNOT.

  The problem: just seeing the `const` keyword doesn't tell you
  whether a variable is usable in a constant expression.
  You have to trace its initializer — and its initializer's initializer
  — which gets messy fast.

  Two more issues with const:
    1. Non-integral const variables (e.g. const double) CANNOT be used
       in constant expressions, even if initialized with a literal.
    2. There's no compile-time enforcement — errors show up late or not at all.

  constexpr solves all of this.
*/

int a { 5 };        // not const at all
const int b { a };  // NOT a constant expression — initializer is a variable
const int c { 5 };  // IS a constant expression — initializer is a literal

// Ambiguous cases — have to trace the origin of someVar / getValue()
const int d { someVar };    // usable in constant expression ONLY IF someVar is one
const int e { getValue() }; // usable in constant expression ONLY IF getValue() returns constexpr


// ────────────────────────────────────────────────────────────
//  PART 2: constexpr VARIABLES
// ────────────────────────────────────────────────────────────

/*
  constexpr = "constant expression" (shorthand keyword)

  A constexpr variable is ALWAYS a compile-time constant.
  It MUST be initialized with a constant expression — otherwise
  you get a compile error immediately. No ambiguity, no tracing.

  Key benefits over const:
    - Works for non-integral types (double, float, etc.)
    - Compile-time enforcement — errors are caught early
    - Explicitly signals intent: "this is always a compile-time constant"
*/

#include <iostream>

// Non-constexpr function — return value is NOT a constant expression
int five() {
    return 5;
}

int main() {
    constexpr double gravity { 9.8 };  // OK — works for non-integral types too
    constexpr int sum { 4 + 5 };       // OK — expression of literals
    constexpr int something { sum };   // OK — sum is itself constexpr

    std::cout << "Enter your age: ";
    int age {};
    std::cin >> age;

    // constexpr int myAge { age };    // COMPILE ERROR: age is a runtime variable
    // constexpr int f { five() };     // COMPILE ERROR: five() is not a constexpr function

    /*
      Why does five() fail?
      Functions normally execute at runtime, so their return value is NOT
      a constant expression — even when the return value itself is a literal.
      You need to explicitly mark the function as constexpr to change this.
    */

    return 0;
}


// ────────────────────────────────────────────────────────────
//  PART 3: const vs constexpr — SIDE BY SIDE
// ────────────────────────────────────────────────────────────

/*
  ┌─────────────────┬──────────────────────────────────┬──────────────────────────────────┐
  │                 │             const                │           constexpr              │
  ├─────────────────┼──────────────────────────────────┼──────────────────────────────────┤
  │ Meaning         │ Value cannot change after init   │ Usable in a constant expression  │
  │ Initializer     │ Known at compile-time OR runtime │ Must be known at compile-time    │
  │ Evaluation      │ Can be evaluated at runtime      │ Can be compile-time or runtime   │
  │ Non-integral    │ NOT usable in constant expression│ Usable in constant expression    │
  │ Enforcement     │ No compile-time guarantee        │ Compile error if invalid         │
  └─────────────────┴──────────────────────────────────┴──────────────────────────────────┘

  constexpr variables are IMPLICITLY const.
  const variables are NOT implicitly constexpr
    — except: const integral variables with a constant expression initializer.
*/


// ────────────────────────────────────────────────────────────
//  PART 4: constexpr FUNCTIONS
// ────────────────────────────────────────────────────────────

/*
  A constexpr function CAN be called in a constant expression.

  RULES:
    1. If the result is used where a constant expression is REQUIRED
       (e.g. initializer of a constexpr variable) → MUST evaluate at compile-time.

    2. If the arguments are constant expressions but context doesn't require it
       → MAY evaluate at compile-time (compiler decides).

    3. If arguments are NOT constant expressions (e.g. runtime variables)
       → evaluates at RUNTIME like a normal function.

  In one line:
    constexpr functions are ELIGIBLE for compile-time evaluation.
    Whether they actually run at compile-time depends on context.
*/

#include <iostream>

// Non-constexpr function
int max(int x, int y) {
    return (x > y) ? x : y;
}

// constexpr function
constexpr int cmax(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    int m1 { max(5, 6) };            // OK — runtime
    const int m2 { max(5, 6) };      // OK — runtime
    // constexpr int m3 { max(5, 6) };  // COMPILE ERROR: max() is not constexpr

    int m4 { cmax(5, 6) };           // OK — compile-time or runtime (compiler decides)
    const int m5 { cmax(5, 6) };     // OK — compile-time or runtime (compiler decides)
    constexpr int m6 { cmax(5, 6) }; // OK — MUST evaluate at compile-time (constexpr context)

    return 0;
}


// ────────────────────────────────────────────────────────────
//  QUICK REFERENCE
// ────────────────────────────────────────────────────────────

/*
  constexpr variable  → always compile-time constant, must be init with constant expression
  constexpr function  → eligible for compile-time execution, actual timing depends on context

  When IS compile-time execution forced?
    → When the result is used in a constexpr variable initializer
    → When used as a template argument
    → When used as an array size

  When is it runtime?
    → When any argument is a runtime variable (e.g. from cin)
    → When the result is stored in a non-constexpr variable (may still optimize, not guaranteed)
*/