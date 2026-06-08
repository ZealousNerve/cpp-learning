// ============================================================
//  CHAPTER 11 — FUNCTION TEMPLATES  (11.6 / 11.7 / 11.8 / 11.9 / 11.10)
//  Topics: intro · instantiation · multi-type · non-type params · multi-file
//  Notes: comprehensive, revision-ready, example-driven
// ============================================================

#include <iostream>
#include <string>
#include <type_traits>   // for std::common_type_t
#include <cassert>
#include <cmath>         // for std::sqrt


// ══════════════════════════════════════════════════════════════
//  11.6  WHAT IS A FUNCTION TEMPLATE?
// ══════════════════════════════════════════════════════════════
//
//  THE PROBLEM (without templates):
//  If you want max() to work for multiple types, you'd have to write
//  a separate overload for each type — that's code duplication (violates DRY):
//
//    int    max(int    x, int    y) { return (x < y) ? y : x; }
//    double max(double x, double y) { return (x < y) ? y : x; }
//    // ... one per type — maintenance nightmare
//
//  Also, a user might call max() with a type you never wrote an overload for.
//
//  THE SOLUTION — Function Templates:
//  Write ONE template definition with a *placeholder type*. The compiler
//  generates ("instantiates") concrete functions from it on demand.
//
//  ANALOGY — think of a stencil:
//  The stencil (template) is created once. Each time you use it, you
//  choose a color (actual type). The stencil itself doesn't have a color;
//  the color is decided at the time of use — not at the time of creation.
//  Templates work the same way: the actual type is decided when the
//  template is *called*, not when it is *written*.
//
//  KEY INSIGHT: Templates can work with types that didn't even exist
//  when the template was written (e.g., your own custom classes).

// ── SYNTAX ───────────────────────────────────────────────────
//
//  template <typename T>   ← template parameter declaration
//  T max(T x, T y)         ← T is the placeholder (type template parameter)
//  {
//      return (x < y) ? y : x;
//  }
//
//  • 'typename' and 'class' are interchangeable in this context.
//    Prefer 'typename' — it makes clear T can be any type, not just a class.
//  • Each function/class template needs its OWN template parameter declaration.
//  • The scope of <typename T> is strictly limited to the template that follows it.

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
    // Uses < instead of > — consistent with how std::max is defined
}

// ── NAMING CONVENTIONS ───────────────────────────────────────
//
//  Trivial/obvious usage:   T, U, V  (single capital letter starting at T)
//  Non-obvious/constrained: Allocator  (standard lib style)
//                           TAllocator (T-prefix style, makes template params stand out)
//
//  Example from std::max:
//    template<class T, class Compare>
//    const T& max(const T& a, const T& b, Compare comp);
//    → T = any comparable type, Compare = must satisfy Compare requirements

// ── 3 KINDS OF TEMPLATE PARAMETERS (for reference) ──────────
//
//  1. Type template parameters      → placeholder for a TYPE   (this chapter)
//  2. Non-type template parameters  → placeholder for a VALUE  (11.9)
//  3. Template template parameters  → placeholder for a TEMPLATE (advanced, not covered here)


// ══════════════════════════════════════════════════════════════
//  11.7  FUNCTION TEMPLATE INSTANTIATION
// ══════════════════════════════════════════════════════════════
//
//  A function template is NOT a function — it's a recipe.
//  It is never compiled or executed directly.
//  The compiler uses it to GENERATE (instantiate) actual functions.
//
//  INSTANTIATION = compiler clones the template and replaces T with a real type.
//
//  Calling max<int>(1, 2) makes the compiler generate this behind the scenes:
//    template <>
//    int max<int>(int x, int y) { return (x < y) ? y : x; }
//
//  Terminology:
//    Primary template   → the original template definition you write
//    Specialization     → a function generated from the primary template
//    Implicit instantiation → happens automatically when you call the template
//
//  A template is instantiated ONCE per unique type per translation unit.
//  Calling max<int> 100 times → still only ONE instantiation of max<int>.

// ── 3 WAYS TO CALL A FUNCTION TEMPLATE ──────────────────────
//
//  1. Explicit type argument:   max<int>(1, 2)
//     → You tell the compiler which type to use. Compiler doesn't guess.
//
//  2. Empty angle brackets:     max<>(1, 2)
//     → Forces template version; compiler deduces T from args.
//     → Non-template overloads are NOT considered.
//
//  3. Normal call syntax:       max(1, 2)         ← PREFERRED
//     → Compiler considers BOTH template and non-template overloads.
//     → If a non-template function also matches → non-template is preferred.

// ── NON-TEMPLATE PREFERRED OVER TEMPLATE ────────────────────

// Non-template version for bool (more specialized behavior):
void printBool(bool x)
{
    std::cout << std::boolalpha << x << '\n';  // prints "true"/"false"
}

// Template version (generic, prints as 1/0 for bool):
template <typename T>
void printTemplate(T x)
{
    std::cout << x << '\n';
}

// printBool(true)        → calls non-template → "true"
// printTemplate<>(true)  → forces template → "1"
// printTemplate<bool>(true) → explicit template → "1"
//
// WHY prefer non-template? It can have a more optimized or specialized
// implementation for that specific type than the generic template.

// ── TEMPLATE ARGUMENT DEDUCTION ──────────────────────────────
//
//  When you call max(1, 2), the compiler sees both args are int,
//  deduces T = int, and instantiates max<int>(int, int).
//
//  IMPORTANT: No type conversion happens during deduction.
//    max(2, 3.5) → fails — one arg is int, other is double.
//                  Compiler can't pick a single T that satisfies both.
//    (Solution: see below later)

// ── INSTANTIATED FUNCTIONS THAT DON'T COMPILE ───────────────

template <typename T>
T addOne(T x) { return x + 1; }

// addOne(5)        → ok: int + 1 works
// addOne(2.3)      → ok: double + 1 works
// addOne("hello")  → COMPILE ERROR: can't add int to const char*
//                    The template is syntactically valid, but breaks when
//                    instantiated with std::string or const char*.

// ── BLOCKING A BAD INSTANTIATION WITH = delete ───────────────
//
//  You can explicitly forbid certain types using template specialization + = delete:

template <>
const char* addOne<const char*>(const char* x) = delete;
// Now addOne("hello") will give a COMPILE ERROR instead of silently doing
// pointer arithmetic (which would be syntactically valid but semantically wrong).

// ── SEMANTICALLY WRONG BUT COMPILES ──────────────────────────
//
//  addOne("Hello, world!") — without the = delete above, this COMPILES.
//  C++ allows int + pointer arithmetic, so the template generates valid code.
//  It produces "ello, world!" (pointer shifted by 1). Correct syntax, wrong semantics.
//  → Always think about what types make sense for your template.

// ── STATIC LOCAL VARIABLES IN TEMPLATES ─────────────────────
//
//  Each instantiated specialization gets its OWN copy of static locals.
//  They are NOT shared across specializations.

template <typename T>
void countCalls()
{
    static int id = 0;
    std::cout << ++id << '\n';
}

// countCalls<int>()    → 1
// countCalls<int>()    → 2   (same specialization, same static)
// countCalls<double>() → 1   (DIFFERENT specialization, its own static)
//
// Compiler generates two separate functions with two separate 'id' variables:
//   void countCalls<int>()    { static int id=0; cout << ++id; }
//   void countCalls<double>() { static int id=0; cout << ++id; }

// ── DEFAULT ARGUMENTS FOR NON-TEMPLATE PARAMETERS ────────────
//
//  Function templates can have default arguments for non-template parameters.
//  Every instantiation uses the same default.

template <typename T>
void printRepeat(T val, int times = 1)
{
    while (times--)
        std::cout << val;
    std::cout << '\n';
}
// printRepeat(5)       → prints: 5        (times defaults to 1)
// printRepeat('a', 3)  → prints: aaa


// ══════════════════════════════════════════════════════════════
//  11.8  FUNCTION TEMPLATES WITH MULTIPLE TEMPLATE TYPES
// ══════════════════════════════════════════════════════════════
//
//  PROBLEM: max(2, 3.5) fails with a single T.
//  T can only be ONE type per call. The compiler won't convert during deduction.
//  You'd get: "template parameter T is ambiguous — could be int or double"

// ── FIX 1: static_cast at call site (works but ugly) ─────────
//
//   max(static_cast<double>(2), 3.5)  → both args now double → T = double → ok
//   Burden on the caller. Not scalable.

// ── FIX 2: explicit type argument (better) ───────────────────
//
//   max<double>(2, 3.5)
//   → You specify T = double. Compiler then implicitly converts int arg to double.
//   → Type conversion IS allowed when you provide an explicit type argument
//     (deduction is bypassed entirely).

// ── FIX 3: Two template type parameters (BEST) ───────────────

template <typename T, typename U>
auto betterMax(T x, U y)
{
    return (x < y) ? y : x;
}
// T and U are INDEPENDENT — each resolves separately from its argument.
// betterMax(2, 3.5) → T=int, U=double
// The ternary operator ?: uses arithmetic conversion rules to find a common
// type (double), so the result is double. No data loss.

// ── WHY NOT use T as return type? ────────────────────────────
//
//  template<typename T, typename U>
//  T badMax(T x, U y) { return (x<y)?y:x; }
//
//  badMax(2, 3.5) → return type is T=int.
//  The actual result 3.5 gets NARROWED to int 3. Silent data loss!
//  → Use 'auto' return type instead (compiler deduces from return expression).

// ── FORWARD-DECLARABLE VERSION (explicit return type) ─────────
//
//  'auto' return requires the full definition to be visible.
//  If you need a forward declaration, use std::common_type_t:

template <typename T, typename U>
auto forwardableMax(T x, U y) -> std::common_type_t<T, U>;
// std::common_type_t<int, double> → double
// Defined in <type_traits>. Forward declaration only shown here;
// the definition below closes it out:

template <typename T, typename U>
auto forwardableMax(T x, U y) -> std::common_type_t<T, U>
{
    return (x < y) ? y : x;
}

// ── C++20 ABBREVIATED FUNCTION TEMPLATES ─────────────────────
//
//  Using 'auto' as a parameter type turns the function into a template automatically.
//  Each 'auto' parameter becomes an independent template type parameter.
//
//    auto max(auto x, auto y) { return (x<y)?y:x; }
//
//  This is EXACTLY equivalent to:
//    template<typename T, typename U> auto max(T x, U y) { return (x<y)?y:x; }
//
//  Use abbreviated form when each parameter should be an independent type.
//  There's no concise abbreviated form for "both parameters must be the SAME type"
//  (for that, stick with template<typename T> T max(T x, T y)).

// ── TEMPLATE OVERLOADING ─────────────────────────────────────
//
//  Templates can be overloaded just like regular functions.
//  "Partial ordering" rules determine which overload is preferred:
//  the MORE restrictive (fewer template params) template wins.

template <typename T>
auto add(T x, T y) { return x + y; }            // same-type (more restrictive)

template <typename T, typename U>
auto add(T x, U y) { return x + y; }            // different-type

template <typename T, typename U, typename V>
auto add(T x, U y, V z) { return x + y + z; }  // 3-arg

// add(1.2, 3.4) → both double → prefers T,T version (more restrictive)
// add(5, 7.0)   → int, double → uses T,U version
// add(1, 2, 3)  → uses T,U,V version
//
// If multiple templates match and none is more restrictive → compiler errors with "ambiguous match".


// ══════════════════════════════════════════════════════════════
//  11.9  NON-TYPE TEMPLATE PARAMETERS
// ══════════════════════════════════════════════════════════════
//
//  A non-type template parameter is NOT a type placeholder.
//  It's a CONSTEXPR VALUE placeholder — baked into the function at compile time.
//
//  Convention: N for int non-type parameters (like T for type parameters).
//
//  Allowed types for non-type parameters:
//    • Integral types (int, char, bool, long, etc.)
//    • Enumeration types
//    • std::nullptr_t
//    • Floating point (C++20 only)
//    • Pointer or reference to an object
//    • Pointer or reference to a function
//    • Pointer or reference to a member function
//    • Literal class types (C++20)

template <int N>
void printN()
{
    std::cout << N << '\n';
}
// printN<5>()  → compiler generates: void printN<5>() { cout << 5; }
// printN<42>() → compiler generates: void printN<42>() { cout << 42; }
//
// You CANNOT pass a runtime variable:
//   int x = 5; printN<x>(); → COMPILE ERROR (x is not constexpr)

// ── WHY USE NON-TYPE PARAMETERS? ─────────────────────────────
//
//  Function parameters (even in constexpr/consteval functions) CANNOT be constexpr.
//  Non-type template parameters ARE constexpr at the point of use.
//  This lets you use them with static_assert, if constexpr, array sizes, etc.
//
//  Runtime function parameter version (limited — can only runtime-assert):
double getSqrt_runtime(double d)
{
    assert(d >= 0.0 && "getSqrt(): d must be non-negative");
    return (d >= 0) ? std::sqrt(d) : 0.0;
    // Problem: -5.0 is a compile-time constant, but the check only fires at RUNTIME
}

//  Non-type template parameter version (catches error at COMPILE TIME):
template <double D>    // C++20 required for floating-point non-type params
double getSqrt()
{
    static_assert(D >= 0.0, "getSqrt(): D must be non-negative");
    if constexpr (D >= 0.0)
        return std::sqrt(D);
    return 0.0;
}
// getSqrt<5.0>()   → compiles fine, returns ~2.236
// getSqrt<-5.0>()  → COMPILE ERROR: static_assert fires
//                    Error caught before the program even runs!
//
// Real-world example you've already seen: std::bitset
//   std::bitset<8> bits { 0b0000'0101 };
//   The <8> is a non-type template argument telling bitset how many bits to store.

// ── IMPLICIT CONVERSIONS FOR NON-TYPE ARGUMENTS ──────────────
//
//  Some constexpr conversions ARE allowed when matching non-type args:
//    ✅ Integral promotions    (char → int)
//    ✅ Integral conversions   (char → long, int → char)
//    ✅ User-defined conversions
//    ✅ Lvalue-to-rvalue
//    ❌ Floating point ↔ integral (NOT allowed — stricter than list-init)

// Example — char to int promotion is allowed:
// printN<'c'>()  → 'c' (char, value 99) converts to int 99 → prints 99

// ── AMBIGUOUS MATCH WITH OVERLOADED NON-TYPE PARAMS ──────────
//
//  If you overload templates for different non-type types, BOTH
//  direction of conversion may match, causing ambiguity:
//
//    template <int N>  void print() { cout << N; }
//    template <char N> void print() { cout << N; }
//
//    print<5>();    → ambiguous: int N=5 OR char N=5 both viable
//    print<'c'>();  → ambiguous: int N=99 OR char N='c' both viable
//
//  Solution: don't overload for multiple non-type types unless you're sure.

// ── C++17: auto NON-TYPE PARAMETER (type deduction) ──────────
//
//  <auto N> lets the compiler deduce the TYPE of the non-type parameter
//  from the template argument — similar to auto variable type deduction.

template <auto N>
void autoPrint()
{
    std::cout << N << '\n';
}
// autoPrint<5>()    → N deduced as int, prints 5
// autoPrint<'c'>()  → N deduced as char, prints c
//
// No ambiguity here — there's only one template. The compiler deduces the type
// and generates distinct specializations (print<5> and print<'c'>) with no conflict.
//
// After instantiation, it looks like:
//   template<> void autoPrint<5>()   { cout << 5; }   // int
//   template<> void autoPrint<'c'>() { cout << 'c'; } // char


// ══════════════════════════════════════════════════════════════
//  11.10  USING FUNCTION TEMPLATES IN MULTIPLE FILES
// ══════════════════════════════════════════════════════════════
//
//  THE PROBLEM — why you can't split templates into .h + .cpp like normal functions:
//
//  Normal function:
//    foo.h   → declaration:  void foo();
//    foo.cpp → definition:   void foo() { ... }
//    main.cpp → #include "foo.h", calls foo() → linker finds definition in foo.cpp ✅
//
//  Function template — this BREAKS:
//
//    add.h   → declaration:  template<typename T> T addOne(T x);
//    add.cpp → definition:   template<typename T> T addOne(T x) { return x+1; }
//    main.cpp → #include "add.h", calls addOne(1) and addOne(2.3)
//
//  What goes wrong:
//    • main.cpp sees only the declaration → compiler trusts the linker will find it
//    • add.cpp has the definition, but NO calls to addOne → compiler instantiates NOTHING
//    • Linker can't find addOne<int> or addOne<double> → LINKER ERROR
//
//  Why? Templates are not functions. The compiler needs to SEE the full template
//  DEFINITION at the point where it needs to instantiate. A declaration isn't enough.
//  The compiler can only instantiate what it can fully see in the current TU.
//
//  THE SOLUTION — put the full template DEFINITION in the header file:
//
//  ┌─── max.h ───────────────────────────────────────────────┐
//  │  #ifndef MAX_H                                          │
//  │  #define MAX_H                                          │
//  │                                                         │
//  │  template <typename T>                                  │
//  │  T max(T x, T y)          ← FULL DEFINITION in header  │
//  │  { return (x < y) ? y : x; }                           │
//  │                                                         │
//  │  #endif                                                 │
//  └─────────────────────────────────────────────────────────┘
//
//  Any .cpp file that needs max<T> just does #include "max.h".
//  The preprocessor copies the definition into each translation unit.
//  The compiler can now instantiate any types needed in that TU.
//
//  WHY DOESN'T THIS VIOLATE THE ODR (One Definition Rule)?
//
//  ODR rule: typically, each function can only be defined ONCE across the whole program.
//  But there are explicit exemptions:
//    → Types, templates, inline functions, inline variables MAY appear identically
//      in multiple files.
//    → Template definitions are ODR-exempt: identical copies in multiple files are fine.
//    → Functions instantiated from templates are implicitly INLINE:
//      inline functions can be defined in multiple files (as long as definitions match).
//
//  Summary:
//    Template definition in multiple files    → ODR-exempt (templates are exempt)
//    Instantiated functions in multiple files → ODR-fine  (they're implicitly inline)
//    The templates themselves are NOT inline  (inline only applies to variables/functions)


// ══════════════════════════════════════════════════════════════
//  GENERIC PROGRAMMING — THE BIG PICTURE
// ══════════════════════════════════════════════════════════════
//
//  Template types are sometimes called "generic types" because they can be
//  any type. Programming with templates is called "generic programming."
//
//  In regular C++, you focus heavily on types.
//  In generic programming, you focus on the LOGIC of algorithms and
//  data structures — types are filled in later.
//
//  The entire C++ Standard Library (std::vector, std::sort, std::max, etc.)
//  is built on templates. Understanding templates = understanding the STL.
//
//  TRADEOFFS:
//    ✅ One definition works for any type
//    ✅ Type-safe (each instantiation is fully type-checked)
//    ✅ Works with types that didn't exist when the template was written
//    ❌ Each unique call with a new type = new compiled function (code bloat)
//    ❌ Compile times increase with many instantiations
//    ❌ Error messages can be long and hard to read
//       (but the actual bug is usually simple once you know what to look for)
//
//  BEST PRACTICE: write a normal function first. Convert to a template
//  only when you find yourself needing overloads for different types.


// ══════════════════════════════════════════════════════════════
//  SUMMARY TABLE
// ══════════════════════════════════════════════════════════════
//
//  Concept                     Key point
//  ──────────────────────────  ────────────────────────────────────────────────
//  Function template           Single definition → compiler generates many functions
//  Primary template            The template you write; source of all instantiations
//  Instantiation               Compiler substitutes T with a real type; generates code
//  Implicit instantiation      Happens automatically on first call with that type
//  Template arg deduction      Compiler infers T from argument types (no conversions)
//  Explicit type argument      max<int>(x, y) — you tell the compiler the type
//  Non-template preferred      Normal call syntax prefers non-template over template
//  = delete specialization     Forbid template instantiation for specific types
//  Static locals per spec.     Each specialization has its own copy of static locals
//  Default args (non-T param)  Allowed; same default across all instantiations
//  Multiple type params        <typename T, typename U> → T and U resolve independently
//  auto return type            Compiler deduces return type from return expression
//  std::common_type_t<T,U>     Explicit common type for forward-declarable templates
//  Abbreviated templates(C++20) auto params → each auto = independent template type
//  Template overloading        Multiple templates for same name; most restrictive wins
//  Non-type template param     constexpr value placeholder, NOT a type
//  N naming convention         int non-type params conventionally named N
//  auto non-type param(C++17)  <auto N> → compiler deduces type of N from argument
//  Non-type implicit convert   Integral promotions/conversions allowed; fp↔int not
//  Non-type overload ambiguity Both directions of conversion may match → ambiguous
//  Templates in headers        Full definition must be in header, not .cpp
//  ODR exemption               Template definitions + implicitly-inline instances OK in multiple files


int main()
{
    // ── 11.6 / 11.7 — basic template usage ──────────────────
    std::cout << "=== 11.6/11.7 ===\n";
    std::cout << max<int>(3, 7)    << '\n';   // explicit: 7
    std::cout << max(3.0, 7.5)     << '\n';   // deduced:  7.5
    std::cout << max(3, 7)         << '\n';   // deduced:  7

    printBool(true);               // non-template preferred → "true"
    printTemplate<>(true);         // forces template → "1"

    countCalls<int>();             // 1
    countCalls<int>();             // 2  (same specialization)
    countCalls<double>();          // 1  (separate static variable)

    printRepeat(5);                // "5"     (times defaults to 1)
    printRepeat('a', 3);           // "aaa"

    // ── 11.7 — addOne with = delete guard ───────────────────
    std::cout << addOne(5)   << '\n';   // 6
    std::cout << addOne(2.3) << '\n';   // 3.3
    // addOne("hello")  → compile error (= delete specialization blocks it)

    // ── 11.8 — multiple template types ──────────────────────
    std::cout << "\n=== 11.8 ===\n";
    std::cout << betterMax(2, 3.5)       << '\n';   // 3.5 (no narrowing)
    std::cout << forwardableMax(2, 3.5)  << '\n';   // 3.5 (explicit return type)
    std::cout << add(1.2, 3.4)           << '\n';   // 4.6  (T,T version)
    std::cout << add(5, 7.0)             << '\n';   // 12   (T,U version)
    std::cout << add(1, 2, 3)            << '\n';   // 6    (T,U,V version)

    // ── 11.9 — non-type template parameters ─────────────────
    std::cout << "\n=== 11.9 ===\n";
    printN<5>();                   // 5
    printN<42>();                  // 42
    printN<'c'>();                 // 99  ('c' converted to int via integral promotion)

    // getSqrt<-1.0>();            // COMPILE ERROR: static_assert (uncomment to test)
    std::cout << getSqrt<9.0>()  << '\n';   // 3

    autoPrint<5>();                // 5   (N deduced as int)
    autoPrint<'c'>();              // c   (N deduced as char)

    return 0;
}

// ══════════════════════════════════════════════════════════════
//  WHAT TO PUT IN .h vs .cpp — CHEAT SHEET
// ══════════════════════════════════════════════════════════════
//
//  Regular function:
//    foo.h   → declaration only:   void foo();
//    foo.cpp → definition:         void foo() { ... }
//
//  Function template:
//    max.h   → full definition:    template<typename T> T max(T x, T y) { ... }
//    (no .cpp needed for the template itself)
//
//  If a function template is only used in ONE .cpp file, you CAN define it
//  in that .cpp file. But the moment another file needs it, move it to a header.