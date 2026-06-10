#include <iostream>
#include <typeinfo>  // for typeid()
#include <cstddef>   // for legacy NULL (awareness only)


// ─────────────────────────────────────────────────────────────
//  BACKGROUND
//  Every variable lives at a unique memory address. When you
//  write  char x {};  the compiler assigns x some address
//  (e.g. 140) and silently uses it every time you write 'x'.
//  References work the same way — a reference is just another
//  name for the same address; the compiler handles everything
//  implicitly. Pointers let YOU hold and use that address explicitly.
// ─────────────────────────────────────────────────────────────


// ═════════════════════════════════════════════════════════════
//  1.  ADDRESS-OF OPERATOR  &
//      Returns a POINTER (not a raw integer literal) whose
//      value is the memory address of the operand.
// ═════════════════════════════════════════════════════════════

void demo_address_of()
{
    int x { 5 };
    std::cout << x  << '\n';  // value   → 5
    std::cout << &x << '\n';  // address → e.g. 0027FEA0  (hex, no 0x prefix)

    // For multi-byte objects, & gives the address of the FIRST byte.

    // typeid confirms &x is a pointer, not an integer:
    std::cout << typeid(x).name()  << '\n';  // int   (or "i" on gcc)
    std::cout << typeid(&x).name() << '\n';  // int * (or "pi" on gcc)
}

// ── Context disambiguation for & ─────────────────────────────
//   int& ref       → lvalue reference  (after a type name)
//   &x             → address-of        (unary, in an expression)
//   x & y          → bitwise AND       (binary, in an expression)


// ═════════════════════════════════════════════════════════════
//  2.  DEREFERENCE OPERATOR  *
//      Given an address, returns the VALUE stored there as an lvalue.
//      address-of and dereference are exact OPPOSITES.
// ═════════════════════════════════════════════════════════════

void demo_dereference()
{
    int x { 5 };
    std::cout << x      << '\n';  // 5
    std::cout << &x     << '\n';  // address
    std::cout << *(&x)  << '\n';  // 5 — dereference the address → back to value

    // * here is UNARY (one operand).
    // Multiplication * is BINARY (two operands). That's how you tell them apart.
}


// ═════════════════════════════════════════════════════════════
//  3.  WHAT IS A POINTER?
//      An OBJECT that stores a memory address as its value.
//      Also called "raw pointer" or "dumb pointer" in modern C++,
//      to distinguish from smart pointers introduced later (ch.22).
// ═════════════════════════════════════════════════════════════

//  Declaration syntax ──────────────────────────────────────────
//    int;    →  plain int
//    int&;   →  lvalue reference to int
//    int*;   →  pointer to int   ← * is part of the TYPE, not a dereference

//  Best practice: put the * next to the TYPE name.
//
//  GOTCHA — multiple declarations on one line:
//    int* ptr1, ptr2;    // WRONG: ptr1 is int*, but ptr2 is a plain int!
//    int* ptr1, *ptr2;   // correct: both are int*
//  → Avoid declaring multiple pointer variables on one line.

void demo_pointer_basics()
{
    int x    { 5 };
    int& ref { x };   // reference: compiler does address-of + dereference implicitly
    int* ptr { &x };  // pointer:   you hold the address explicitly

    std::cout << x    << '\n';  // 5
    std::cout << ref  << '\n';  // 5
    std::cout << *ptr << '\n';  // 5 — must dereference manually

    // ptr is "pointing to" x — that's where the name comes from.
    // "An integer pointer" = "a pointer to an integer".
}


// ═════════════════════════════════════════════════════════════
//  4.  POINTER INITIALIZATION
// ═════════════════════════════════════════════════════════════
//
//  Wild pointer  → declared but NOT initialized → holds a garbage address
//                  dereferencing it = UNDEFINED BEHAVIOR → probable crash
//
//  ALWAYS initialize every pointer.

void demo_initialization()
{
    int x { 5 };

    int* wild;            // ❌ uninitialized (wild pointer) — NEVER do this
    int* null_ptr {};     // ✅ value-initialized → null pointer (points at nothing, safely)
    int* ptr { &x };      // ✅ initialized with the address of x

    // Type-matching rule: pointer type must match the pointed-to type.
    double d { 7.0 };
    // int*    bad  { &d };  // ❌ int* cannot point at a double
    double* dPtr { &d };     // ✅

    // Literal values are NOT valid initializers (except nullptr / 0 — see section 7):
    // int* p { 5 };            // ❌
    // int* p { 0x0012FF7C };   // ❌ treated as integer literal, not an address

    (void)wild; (void)null_ptr; (void)ptr; (void)dPtr;
}


// ═════════════════════════════════════════════════════════════
//  5.  POINTER ASSIGNMENT — two distinct operations
// ═════════════════════════════════════════════════════════════

void demo_assignment()
{
    int x { 5 };
    int y { 6 };
    int* ptr { &x };

    // A) Change WHERE the pointer points ──────────────────────
    std::cout << *ptr << '\n';  // 5 (x's value)
    ptr = &y;                   // redirect: ptr now holds y's address
    std::cout << *ptr << '\n';  // 6 (y's value)

    // B) Change the VALUE at the pointed-to address ───────────
    *ptr = 99;                  // modifies y through ptr
    std::cout << y    << '\n';  // 99
    std::cout << *ptr << '\n';  // 99

    // KEY MENTAL MODEL:
    //   ptr        →  the address stored in the pointer
    //   *ptr       →  the object AT that address (lvalue → assignable)
    //   ptr  = &y  →  redirect the pointer to a new address
    //   *ptr = 99  →  overwrite the value of the pointed-to object
}


// ═════════════════════════════════════════════════════════════
//  6.  POINTERS vs LVALUE REFERENCES — side-by-side
// ═════════════════════════════════════════════════════════════

void demo_ptr_vs_ref()
{
    int x { 5 };
    int& ref { x };   // reference
    int* ptr { &x };  // pointer

    std::cout << x << ref << *ptr << '\n';  // 555

    ref  = 6;
    std::cout << x << ref << *ptr << '\n';  // 666

    *ptr = 7;
    std::cout << x << ref << *ptr << '\n';  // 777
    // All three names read the same memory location.
}

// ── Differences to memorize ──────────────────────────────────
//
//  REFERENCES                          POINTERS
//  Must be initialized                 Need not be (but should be)
//  Not objects themselves              Are objects
//  Cannot be re-seated                 Can point at something different
//  Must always be bound to an object   Can hold null (point at nothing)
//  Implicitly dereference              Require explicit *
//  "Safer" — no null, no wild          Inherently more dangerous


// ═════════════════════════════════════════════════════════════
//  7.  SIZE OF POINTERS
//      Depends on the ARCHITECTURE, never on the pointed-to type.
//        32-bit build → 4 bytes for ALL pointer types
//        64-bit build → 8 bytes for ALL pointer types
// ═════════════════════════════════════════════════════════════

void demo_pointer_size()
{
    char*        chPtr  {};
    int*         iPtr   {};
    long double* ldPtr  {};

    // On a 32-bit build all print 4; on 64-bit all print 8.
    std::cout << sizeof(chPtr)  << '\n';
    std::cout << sizeof(iPtr)   << '\n';
    std::cout << sizeof(ldPtr)  << '\n';
}


// ═════════════════════════════════════════════════════════════
//  8.  DANGLING POINTERS
//      A pointer holding the address of an object that no longer exists.
//      Dereferencing a dangling pointer → UNDEFINED BEHAVIOR.
// ═════════════════════════════════════════════════════════════

void demo_dangling()
{
    int x { 5 };
    int* ptr { &x };

    std::cout << *ptr << '\n';  // ✅ 5

    {
        int y { 6 };
        ptr = &y;
        std::cout << *ptr << '\n';  // ✅ 6
    }  // y destroyed here → ptr is NOW DANGLING

    // std::cout << *ptr;  // ❌ UB — may print 6 by luck, or crash, or worse

    // IMPORTANT DISTINCTION (from the standard):
    //   Dereferencing  an invalid pointer  = UNDEFINED BEHAVIOR
    //   Assigning      an invalid pointer  = implementation-defined  (e.g. ptr = nullptr is safe)
    // So you can always safely set a dangling pointer to nullptr — just don't dereference it first.

    ptr = nullptr;  // ✅ safe cleanup
}


// ═════════════════════════════════════════════════════════════
//  9.  NULL POINTERS
//      A pointer holding null — meaning it points at NOTHING.
//      Null is a special value distinct from every real address.
// ═════════════════════════════════════════════════════════════

void demo_null_pointers()
{
    // Two correct ways to create a null pointer:
    int* p1 {};           // value-initialization → null (preferred when assigning later)
    int* p2 { nullptr };  // explicit nullptr     (preferred when you want to be obvious)

    // nullptr is a keyword (a pointer literal), just like true/false are bool literals.
    // Use it for: initialization, assignment, and passing to functions.

    int value { 5 };
    int* ptr { &value };
    ptr = nullptr;  // reset: we stop pointing at value (value itself is unaffected)

    // A null pointer is safe to HOLD. It is NEVER safe to DEREFERENCE.
    // int* bad {};
    // std::cout << *bad;  // ❌ UB — crash in practice
    // This is the #1 most common C++ crash.
}


// ═════════════════════════════════════════════════════════════
//  10. CHECKING FOR NULL BEFORE DEREFERENCING
// ═════════════════════════════════════════════════════════════

void someFunction(int* p)
{
    if (p)
        std::cout << "value: " << *p << '\n';
    else
        std::cout << "got nullptr\n";
}

void demo_null_check()
{
    int x { 5 };
    int* ptr     { &x };
    int* nullPtr {};

    // Method A — explicit equality
    if (ptr == nullptr)
        std::cout << "null\n";
    else
        std::cout << "non-null: " << *ptr << '\n';

    // Method B — implicit bool conversion (idiomatic C++)
    // null pointer  → false
    // non-null      → true
    if (ptr)           std::cout << "non-null\n";
    if (!nullPtr)      std::cout << "null\n";

    // Ternary:
    std::cout << (ptr ? "non-null" : "null") << '\n';

    someFunction(nullptr);  // explicit null argument
    someFunction(&x);

    // ── CRITICAL LIMITATION ──────────────────────────────────
    // A null-check tells you ONLY "null or not null".
    // It CANNOT detect a DANGLING pointer.
    // There is NO built-in way to detect a dangling pointer.
    // You must prevent dangling pointers through good coding habits.
}


// ═════════════════════════════════════════════════════════════
//  11. USING nullptr AS A SAFETY STRATEGY
//      Keep every pointer either (a) pointing at a valid live object
//      OR (b) set to nullptr. Then a null-check before every
//      dereference is sufficient.
// ═════════════════════════════════════════════════════════════

void demo_null_strategy()
{
    int* ptr { nullptr };

    {
        int x { 5 };
        ptr = &x;
        std::cout << *ptr << '\n';  // ✅ 5
    }
    // x destroyed; ptr is dangling — nullify it immediately:
    ptr = nullptr;

    if (ptr)
        std::cout << *ptr;          // skipped — ptr is null → no UB
    else
        std::cout << "safely handled\n";

    // FACT: When an object is destroyed, its pointers are NOT automatically
    //       set to nullptr. That is YOUR responsibility.
}

// Why a null-check alone isn't always enough — classic pitfall:
void demo_null_check_not_enough()
{
    int* ptr {};
    {
        int x { 5 };
        ptr = &x;
    }
    // x is gone; ptr is dangling (NOT null)

    if (ptr)               // evaluates TRUE — ptr is not null!
        // std::cout << *ptr;  // ❌ UB — dangling, not null
        std::cout << "ptr is non-null but dangling — null check didn't save us\n";
}


// ═════════════════════════════════════════════════════════════
//  12. LEGACY NULL LITERALS — for reading old code only
//      Use nullptr in all new code.
// ═════════════════════════════════════════════════════════════

void demo_legacy_null()
{
    // Literal 0 — pre-C++11 way (still compiles, don't use):
    float* p1 { 0 };
    float* p2 {};
    p2 = 0;

    // NULL macro from <cstddef> — inherited from C (don't use):
    double* p3 { NULL };
    double* p4 {};
    p4 = NULL;

    // WHY nullptr is strictly better than 0 or NULL:
    //   0 is also an integer literal — breaks overload resolution:
    //     void f(int);   void f(int*);
    //     f(0);          // calls f(int) — probably a bug
    //     f(nullptr);    // unambiguously calls f(int*)

    (void)p1; (void)p2; (void)p3; (void)p4;
}


// ═════════════════════════════════════════════════════════════
//  13. POINTERS AND CONST
//      Three combinations. The position of 'const' relative to *
//      is the only thing you need to remember.
// ═════════════════════════════════════════════════════════════

// ─── 13a. POINTER TO CONST VALUE   →   const int* ptr ────────
//
//   const is BEFORE the *  →  the DATA is read-only through this pointer.
//   The pointer itself can be redirected freely.
//
//   "I promise not to change the value I'm looking at through this pointer."

void demo_ptr_to_const()
{
    const int x { 5 };
    // int* bad { &x };       // ❌ would allow modifying a const variable
    const int* ptr { &x };   // ✅

    // *ptr = 6;              // ❌ can't modify through pointer-to-const
    const int y { 6 };
    ptr = &y;                 // ✅ pointer itself is not const — can redirect

    // Can point at a NON-const variable too:
    int z { 10 };
    const int* ptr2 { &z };  // ✅ legal
    // *ptr2 = 20;            // ❌ read-only through this pointer
    z = 20;                   // ✅ direct access still works fine

    std::cout << *ptr << ' ' << *ptr2 << '\n';  // 6 20
}


// ─── 13b. CONST POINTER (to non-const value)   →   int* const ptr ──
//
//   const is AFTER the *  →  the POINTER ADDRESS is locked.
//   Must be initialized at declaration. Value can still be changed.
//
//   "This pointer will always point at the same address."

void demo_const_ptr()
{
    int x { 5 };
    int y { 6 };

    int* const ptr { &x };  // must initialize here (like any const)

    // ptr = &y;            // ❌ can't change address
    *ptr = 99;              // ✅ value is non-const — changeable
    std::cout << x << '\n'; // 99
}


// ─── 13c. CONST POINTER TO CONST VALUE   →   const int* const ptr ──
//
//   const BOTH before and after *  →  address locked + data read-only.
//   Can only dereference to READ.

void demo_const_ptr_to_const()
{
    int value { 5 };
    const int* const ptr { &value };

    // ptr   = &value;  // ❌ pointer is const
    // *ptr  = 6;       // ❌ data is const through this pointer
    std::cout << *ptr << '\n';  // ✅ reading is always fine — 5
}


// ═════════════════════════════════════════════════════════════
//  14. READING CONST POINTER DECLARATIONS
//      Read right-to-left, treating * as "pointer to":
//
//  int*             ptr  →  ptr is a [pointer to] int
//  const int*       ptr  →  ptr is a [pointer to] [const int]       (data const)
//  int* const       ptr  →  ptr is a [const pointer to] int         (pointer const)
//  const int* const ptr  →  ptr is a [const pointer to] [const int] (both const)
//
//  Shortcut:
//    const BEFORE * →  data is const (can't change via this pointer)
//    const AFTER  * →  pointer is const (can't redirect)
// ═════════════════════════════════════════════════════════════

void demo_all_four_declarations()
{
    int a { 1 };
    const int b { 2 };

    int*             p1 { &a };  // move ptr? ✅   modify *ptr? ✅
    const int*       p2 { &b };  // move ptr? ✅   modify *ptr? ❌
    int* const       p3 { &a };  // move ptr? ❌   modify *ptr? ✅
    const int* const p4 { &b };  // move ptr? ❌   modify *ptr? ❌

    std::cout << *p1 << *p2 << *p3 << *p4 << '\n';  // 1 2 1 2
}

// ── Summary table ────────────────────────────────────────────
//
//  Declaration            | Can redirect ptr? | Can change *ptr?
//  -----------------------|-------------------|------------------
//  int*             ptr   |        ✅         |       ✅
//  const int*       ptr   |        ✅         |       ❌
//  int* const       ptr   |        ❌         |       ✅
//  const int* const ptr   |        ❌         |       ❌


// ═════════════════════════════════════════════════════════════
//  15. CONST POINTER GOTCHAS
// ═════════════════════════════════════════════════════════════

void demo_const_gotchas()
{
    // GOTCHA 1: non-const pointer CANNOT point at a const variable.
    const int cx { 10 };
    // int* ptr { &cx };     // ❌ compile error — would silently allow mutation of const

    // GOTCHA 2: pointer-to-const CAN point at a non-const variable.
    int x { 20 };
    const int* cptr { &x };  // ✅ legal — just restricts access through cptr
    x = 30;                   // ✅ direct mutation is fine
    // *cptr = 30;            // ❌ restricted through this pointer

    // GOTCHA 3: const pointer must be initialized at declaration.
    // int* const bad;        // ❌ compile error — uninitialized const

    // GOTCHA 4: "pointer to const" does NOT mean the object itself is const.
    // It means: "I promise not to change it THROUGH THIS pointer."

    std::cout << *cptr << '\n';  // 30
}


// ═════════════════════════════════════════════════════════════
//  16. PREFER REFERENCES OVER POINTERS
//      Use a pointer only when you genuinely NEED null or re-pointing.
// ═════════════════════════════════════════════════════════════

//  Why references are safer:
//    • Cannot be null       → no null-dereference risk
//    • Cannot be re-seated  → harder to accidentally create dangling situations
//    • Must be initialized  → no wild-reference equivalent


// ═════════════════════════════════════════════════════════════
//  MASTER CHECKLIST
// ═════════════════════════════════════════════════════════════
//
//  BASICS
//  1.  Always initialize every pointer (to an address or {}).
//  2.  ptr  = &y   → redirect pointer.    *ptr = val → modify pointed-to object.
//  3.  & in expression = address-of.  * unary in expression = dereference.
//  4.  Pointer size = architecture width (4 or 8 bytes), never the pointed type.
//
//  NULL
//  5.  nullptr is the correct null literal in modern C++ — never use 0 or NULL.
//  6.  null pointer → bool false.  non-null pointer → bool true.
//  7.  Null-check before every dereference:  if (ptr) { *ptr ... }
//  8.  Null-check detects null; it CANNOT detect dangling.
//  9.  When a pointed-to object is destroyed → set ptr = nullptr immediately.
//  10. Objects do NOT automatically null their pointers on destruction.
//
//  CONST
//  11. const BEFORE * → data is read-only through this pointer.
//  12. const AFTER  * → pointer address is locked (initialize at declaration).
//  13. const BOTH   → address locked + data read-only.
//  14. Non-const ptr CANNOT point at a const object (prevents silent mutation).
//  15. Pointer-to-const CAN point at non-const objects (limits only that pointer).
//
//  GENERAL
//  16. Prefer references over pointers unless null or re-pointing is needed.
//  17. Dereferencing wild / null / dangling pointer = UB (probable crash).
//  18. Assigning (not dereferencing) an invalid pointer = implementation-defined, safe.


int main()
{
    demo_address_of();
    demo_dereference();
    demo_pointer_basics();
    demo_initialization();
    demo_assignment();
    demo_ptr_vs_ref();
    demo_pointer_size();
    demo_dangling();
    demo_null_pointers();
    demo_null_check();
    demo_null_strategy();
    demo_null_check_not_enough();
    demo_legacy_null();
    demo_ptr_to_const();
    demo_const_ptr();
    demo_const_ptr_to_const();
    demo_all_four_declarations();
    demo_const_gotchas();
    return 0;
}