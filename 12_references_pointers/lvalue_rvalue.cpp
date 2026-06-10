#include <iostream>
#include <string>

// ── PART 1: WHAT IS A VALUE CATEGORY? ──────────────────────────────────────
//
// Every expression has two properties:
//   1. TYPE       → what kind of data the expression produces (int, double, etc.)
//   2. VALUE CAT  → whether the expression is an lvalue or rvalue
//
// This is what lets the compiler catch errors like:
//   5 = x;   // ❌ can't assign to a literal — 5 is a rvalue, not a modifiable lvalue


// ── PART 2: LVALUE ──────────────────────────────────────────────────────────
//
// lvalue = "locator value" / "left value"
// → An expression that evaluates to an IDENTIFIABLE object or function
// → Has an address, has a name, persists beyond the expression
// → Can appear on the LEFT side of assignment (if modifiable)
//
// Two subtypes:
//   • Modifiable lvalue     → regular variables (can be changed)
//   • Non-modifiable lvalue → const / constexpr variables (cannot be changed)

void lvalue_examples()
{
    int x { 5 };
    const double d { 1.2 };

    int y  { x };   // ✅ x  is a MODIFIABLE lvalue   — has identity, can change
    double e { d };  // ✅ d  is a NON-MODIFIABLE lvalue — has identity, can't change

    // "Hello" — C-style string literal is also an lvalue
    // because it decays to a pointer, which requires an address (lvalue behavior)
    // inherited from C for backwards compatibility
}


// ── PART 3: RVALUE ──────────────────────────────────────────────────────────
//
// rvalue = "right value"
// → An expression that is NOT an lvalue
// → Evaluates to a VALUE (not an identifiable object)
// → Temporary — exists only within the scope of the expression
// → Cannot appear on the LEFT side of assignment
//
// Common rvalues:
//   • Numeric/bool/char literals:   5, 3.14, true
//   • Return-by-value results:      return5(), x + 1
//   • Temporary objects:            std::string{"Hello"}
//   • Result of static_cast:        static_cast<int>(d)
//
// ❌ EXCEPT: C-style string literals ("Hello") are lvalues (see above)

int return5() { return 5; }

void rvalue_examples()
{
    int x { 5 };         // 5 is an rvalue
    const double d{1.2}; // 1.2 is an rvalue

    int z  { return5() };           // return5() is an rvalue — returned by value, temporary
    int w  { x + 1 };               // x + 1 is an rvalue — temporary result
    int q  { static_cast<int>(d) }; // static_cast result is an rvalue — temporary
}


// ── PART 4: ASSIGNMENT RULE ─────────────────────────────────────────────────
//
// Assignment:  left operand = MODIFIABLE lvalue
//              right operand = rvalue  (but lvalues auto-convert — see Part 5)

void assignment_rule()
{
    int x {};

    x = 5;   // ✅ x is modifiable lvalue | 5 is rvalue
    // 5 = x; // ❌ 5 is an rvalue — cannot be assigned to
}


// ── PART 5: LVALUE-TO-RVALUE CONVERSION ────────────────────────────────────
//
// Operators usually expect RVALUE operands.
// If you pass an lvalue where an rvalue is expected → implicit conversion occurs.
// The lvalue is EVALUATED to produce its value (an rvalue).
//
// lvalue → rvalue  ✅ (implicit, automatic)
// rvalue → lvalue  ❌ (NOT allowed)

void lvalue_to_rvalue()
{
    int x { 1 };
    int y { 2 };

    x = y;
    // y is an lvalue, but assignment expects rvalue on the right
    // → y undergoes lvalue-to-rvalue conversion → produces value 2 → assigned to x

    x = x + 1;
    // LEFT  side: x is lvalue (assignment target)
    // RIGHT side: x is converted to rvalue (value 1) → 1+1=2 (rvalue) → assigned to x
}


// ── PART 6: PREFIX vs POSTFIX ++ ────────────────────────────────────────────
//
// ++x  (prefix)  → returns the modified variable itself → LVALUE
// x++  (postfix) → returns a COPY of the old value      → RVALUE

void increment_value_category()
{
    int x { 5 };

    // ++x is lvalue  → you can do:  int& ref = ++x;
    // x++ is rvalue  → temporary copy, not identifiable
}


// ── PART 7: QUICK RULE OF THUMB ─────────────────────────────────────────────
//
// ASK: Does this expression evaluate to something with a name/address
//      that persists beyond the expression?
//
//   YES → lvalue   (variables, const vars, C-style strings, ++x)
//   NO  → rvalue   (literals, return-by-value, x+1, x++, temporaries)


// ── PART 8: COMPILER TRICK — DETECT lvalue vs rvalue AT COMPILE TIME ────────
//
// T&  (lvalue ref) overload is chosen for lvalues
// T&& (rvalue ref) overload is chosen for rvalues

template <typename T> constexpr bool is_lvalue(T&)  { return true;  }
template <typename T> constexpr bool is_lvalue(T&&) { return false; }

#define PRINTVCAT(expr) \
    std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue" : "rvalue") << '\n';

void detect_value_category()
{
    int x { 5 };

    PRINTVCAT(5);                    // rvalue  — literal
    PRINTVCAT(return5());            // rvalue  — return by value
    PRINTVCAT(x);                    // lvalue  — named variable
    PRINTVCAT(std::string{"Hello"}); // rvalue  — temporary object
    PRINTVCAT("Hello");              // lvalue  — C-style string (decays to pointer)
    PRINTVCAT(++x);                  // lvalue  — prefix++ returns the variable
    PRINTVCAT(x++);                  // rvalue  — postfix++ returns a copy
}


// ── PART 9: SUMMARY TABLE ───────────────────────────────────────────────────
//
//  Expression              | Value Category | Why
// ─────────────────────────┼────────────────┼─────────────────────────────────
//  int x                   | lvalue         | named variable, has address
//  const double d          | lvalue (non-mod)| named, but can't change
//  5, 3.14, true           | rvalue         | literals, no identity
//  return5()               | rvalue         | returned by value, temporary
//  x + 1                   | rvalue         | operator+ returns temporary
//  static_cast<int>(d)     | rvalue         | cast result is temporary
//  std::string{"Hello"}    | rvalue         | temporary object
//  "Hello"  (C-style)      | lvalue         | C-array → decays to pointer
//  ++x                     | lvalue         | returns modified variable itself
//  x++                     | rvalue         | returns old value copy
//
// NOTE: C++11 added 3 more categories (glvalue, prvalue, xvalue) for move
//       semantics. Covered later. For now, lvalue/rvalue is sufficient.
