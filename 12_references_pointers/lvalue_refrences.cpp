#include <iostream>
#include <string>
#include <string_view>

// ── PART 1 ── WHAT IS A REFERENCE? ──────────────────────────────────────────
/*
  A reference is an ALIAS for an existing object.
  Every operation on the reference applies directly to the original object.
  It is NOT a copy. It IS the object, just under another name.

  Type syntax:
    int        → normal int
    int&       → lvalue reference to int
    double&    → lvalue reference to double
    const int& → lvalue reference to const int

  Always place & next to the TYPE, not the variable name:  ✅ int& ref   ❌ int &ref
*/

void part1_basics() {
    int x { 5 };
    int& ref { x };   // ref is an alias for x — they share the same memory address

    std::cout << x   << '\n';  // 5
    std::cout << ref << '\n';  // 5  ← same value, same object

    ref = 99;
    std::cout << x << '\n';    // 99 ← modifying ref modifies x directly

    // Proof: same address
    std::cout << (&x == &ref) << '\n';  // 1 (true)
}


// ── PART 2 ── RULES OF REFERENCE INITIALIZATION ─────────────────────────────
/*
  RULE 1: References MUST be initialized — no such thing as an unbound reference.
  RULE 2: Non-const lvalue references can ONLY bind to MODIFIABLE lvalues.
  RULE 3: References CANNOT be reseated (re-bound to another object after init).
  RULE 4: References to void are disallowed.

  lvalue  = an expression that identifies a persistent object (has address)
  rvalue  = a temporary value with no persistent address (e.g. literal 5)
*/

void part2_rules() {
    // ❌ int& bad;              → must initialize
    // ❌ const int y{5}; int& r{y};  → can't bind non-const ref to const lvalue
    // ❌ int& r2 { 0 };         → can't bind non-const ref to rvalue

    int a { 10 }, b { 20 };
    int& ref { a };   // ref → a

    ref = b;  // ← this does NOT reseat ref to point at b
              //   it assigns b's VALUE (20) into a
    std::cout << a << '\n';  // 20 ← a was modified, ref still points to a

    // Type must match (or compiler tries conversion → rvalue → error for non-const)
    double d { 3.14 };
    // ❌ int& bad { d };   → conversion produces rvalue, non-const ref can't bind
}


// ── PART 3 ── LIFETIME: REFERENCES ARE NOT OBJECTS ──────────────────────────
/*
  References are NOT objects — they have no guaranteed independent storage.
  The compiler often optimizes them away entirely (replacing ref with the object).

  Lifetimes are INDEPENDENT:
    - ref can die before its referent → no problem
    - referent dies before ref → DANGLING REFERENCE → undefined behavior ⚠

  "Variable" is technically a misnomer for references (variables are objects with names,
   references are neither guaranteed to be objects nor have independent storage).
*/

void part3_lifetime() {
    int x { 5 };

    {
        int& ref { x };
        std::cout << ref << '\n';  // 5
    }   // ref dies here — x is completely unaffected

    std::cout << x << '\n';  // 5 — x lives on

    // Dangling reference example (DO NOT actually do this):
    // int* p = new int{42};
    // int& r = *p;
    // delete p;
    // std::cout << r;  ← UB: referent destroyed before reference
}


// ── PART 4 ── CONST LVALUE REFERENCES ───────────────────────────────────────
/*
  const int& can bind to:
    ✅ modifiable lvalue     (int x)
    ✅ non-modifiable lvalue (const int x)
    ✅ rvalue / literal      (5, 3.14, "hello")
    ✅ different type        (if implicitly convertible)

  When binding to an rvalue or mismatched type:
    → compiler creates a TEMPORARY object of the reference's type
    → reference binds to that temporary
    → temporary's lifetime is EXTENDED to match the reference's lifetime

  ⚠️ WARNING: if types differ, ref and original are now SEPARATE objects.
  Changes to the original are NOT visible through the ref, and vice versa.
*/

void part4_const_ref() {
    // Bind to modifiable lvalue
    int x { 5 };
    const int& r1 { x };
    // r1 = 10;  ❌ can't modify through const ref
    x = 10;    // ✅ can still modify via original name
    std::cout << r1 << '\n';  // 10 — sees the change (same object)

    // Bind to const lvalue
    const int y { 99 };
    const int& r2 { y };     // ✅

    // Bind to rvalue — temporary created, lifetime extended
    const int& r3 { 42 };
    std::cout << r3 << '\n'; // 42 — safe, temporary lives as long as r3

    // Bind to different type — SEPARATE temporary created
    short bombs { 1 };
    const int& you { bombs };  // temporary int{1} created, you binds to IT
    --bombs;                   // bombs = 0, but you still sees 1 (different object!)
    if (you) std::cout << "Still 1!\n";  // prints — this is the warning trap
}


// ── PART 5 ── constexpr REFERENCES (optional / rare) ────────────────────────
/*
  constexpr int& can ONLY bind to objects with STATIC duration:
    ✅ global variables
    ✅ static local variables
    ❌ regular local variables (address not known at compile time)

  When referencing a const variable via constexpr ref, need BOTH keywords:
    constexpr const int& ref { s_x };
*/

int g_val { 10 };

void part5_constexpr_ref() {
    [[maybe_unused]] constexpr int& r1 { g_val };  // ✅ global

    static int s { 5 };
    [[maybe_unused]] constexpr int& r2 { s };      // ✅ static local

    int local { 3 };
    // ❌ constexpr int& r3 { local };  → compile error
}


// ── PART 6 ── PASS BY REFERENCE ─────────────────────────────────────────────
/*
  Pass by VALUE  → argument is COPIED into parameter (new object, new address)
  Pass by REFERENCE → parameter is BOUND to argument (same object, same address)

  WHY it matters:
    - Fundamental types (int, double) → cheap to copy → pass by value is fine
    - Class types (std::string, etc.) → expensive to copy → pass by ref preferred

  Pass by non-const ref → function CAN modify the caller's argument
  Pass by const ref     → function CANNOT modify, but accepts wider range of args
*/

void modifyByValue(int y)  { ++y; }          // only changes local copy
void modifyByRef(int& y)   { ++y; }          // modifies caller's variable directly

void printExpensive(const std::string& s) {  // no copy made
    std::cout << s << '\n';
}

void part6_pass_by_ref() {
    int a { 5 };
    modifyByValue(a);
    std::cout << a << '\n';  // 5 — unchanged

    modifyByRef(a);
    std::cout << a << '\n';  // 6 — modified!

    std::string msg { "Hello, world!" };
    printExpensive(msg);     // bound, not copied
}


// ── PART 7 ── PASS BY CONST REFERENCE ───────────────────────────────────────
/*
  const ref param accepts ALL argument categories:
    ✅ modifiable lvalue
    ✅ non-modifiable lvalue (const variable)
    ✅ rvalue / literal
    ✅ different-but-convertible type (via temporary)

  Non-const ref param accepts ONLY modifiable lvalues.
  → Always prefer const ref unless you specifically need to mutate the argument.

  RULE OF THUMB for function params:
    Fundamental types      → pass by VALUE
    Class / large types    → pass by CONST REFERENCE
    Need to mutate caller  → pass by non-const REFERENCE
*/

void printRef(const int& y) { std::cout << y << '\n'; }

void part7_const_ref_params() {
    int x { 5 };
    const int z { 10 };

    printRef(x);   // ✅ modifiable lvalue
    printRef(z);   // ✅ const lvalue
    printRef(42);  // ✅ rvalue — temporary created

    // Mix of param types in one function:
    // void foo(int a, int& b, const std::string& c)
    //   a → by value, b → by ref (mutable), c → by const ref
}


// ── PART 8 ── std::string_view vs const std::string& ────────────────────────
/*
  When a function takes a string parameter, prefer std::string_view (by VALUE)
  over const std::string& in most cases.

  Why? Cost matrix:

  Argument type       | string_view param    | const string& param
  --------------------|----------------------|---------------------
  std::string         | cheap conversion     | cheap ref bind       ✅ both ok
  std::string_view    | cheap copy           | ❌ needs explicit cast → expensive
  C-style / literal   | cheap conversion     | ❌ expensive std::string created

  string_view handles all 3 cheaply. const string& only handles std::string cheaply.

  ALSO: string_view parameter is a normal object → direct access (1 step)
        const string& parameter → dereference ref first, THEN access (2 steps)

  When const string& is still better:
    - You need to call something that requires null-terminated C-string (string_view not guaranteed null-terminated)
    - You need to call a function that takes std::string& (string_view won't convert back)
    - C++14 or older (string_view not available)
*/

void printSV(std::string_view sv)       { std::cout << sv << '\n'; }
void printCS(const std::string& s)      { std::cout << s  << '\n'; }

void part8_string_view() {
    std::string     s  { "Hello" };
    std::string_view sv { s };

    printSV(s);               // ✅ cheap: string → string_view
    printSV(sv);              // ✅ cheap: copy of string_view
    printSV("Hello");         // ✅ cheap: literal → string_view

    printCS(s);               // ✅ cheap: ref bind
    // printCS(sv);            ❌ compile error: no implicit string_view → string
    printCS(static_cast<std::string>(sv)); // ✅ compiles but EXPENSIVE — makes a copy
    printCS("Hello");         // ✅ compiles but EXPENSIVE — makes a std::string temp
}


// ── SUMMARY ─────────────────────────────────────────────────────────────────
/*
  int&        → alias, must init, only binds modifiable lvalue, cannot reseat
  const int&  → alias, binds everything (lvalue/rvalue/different type via temp)
                temporary lifetime extended to match ref's lifetime

  Pass by value      → copy made,   fundamental types preferred
  Pass by ref        → no copy,     function can mutate caller's object
  Pass by const ref  → no copy,     function cannot mutate, accepts all arg types
  std::string_view   → prefer over const string& for string params (cheaper overall)

  ⚠️ Dangling reference = referent destroyed before ref → undefined behavior
  ⚠️ Binding const ref to different type → separate temporary → original changes invisible
  ⚠️ ref = otherVar does NOT reseat → it ASSIGNS the value into the original object
*/

int main() {
    part1_basics();
    part2_rules();
    part3_lifetime();
    part4_const_ref();
    part5_constexpr_ref();
    part6_pass_by_ref();
    part7_const_ref_params();
    part8_string_view();
    return 0;
}