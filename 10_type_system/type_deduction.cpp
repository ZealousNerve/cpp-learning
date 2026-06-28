#include <iostream>
#include <string>
#include <string_view>

using namespace std;

// ─────────────────────────────────────────────────────────────
//        TYPE DEDUCTION FOR OBJECTS (auto keyword)
// ─────────────────────────────────────────────────────────────

// auto tells the compiler: "figure out the type from the initializer"
// MUST have an initializer — auto a; is a compile error

void objectTypeDeduction() {
    auto d   { 5.0 };     // double  (5.0 is a double literal)
    auto i   { 1 + 2 };   // int     (1+2 yields int)
    auto x   { i };       // int     (i is int)
    auto a   { 1.23f };   // float   (f suffix)
    auto b   { 5u };      // unsigned int (u suffix)

    // auto with const / constexpr
    const auto    ca { 5 };   // const int
    constexpr auto ce { 5 };  // constexpr int (implicitly const)

    // TRAP: auto drops const from the initializer's type
    const int p { 5 };
    auto q { p };             // q is int, NOT const int — const was dropped
    const auto r { p };       // r is const int — you re-added it manually

    // constexpr case — same rule
    constexpr double pi { 3.14 };
    auto       pi2 { pi };    // double  (const dropped)
    const auto pi3 { pi };    // const double
    constexpr auto pi4 { pi };// const double (constexpr re-applies const)

    // auto with function return value
    // auto sum { add(5, 6) };  // deduced as whatever add() returns

    // STRING TRAP — very easy to forget
    auto s1 { "hello" };          // const char*, NOT std::string
    // fix:
    using namespace std::literals;
    auto s2 { "hello"s };         // std::string
    auto s3 { "hello"sv };        // std::string_view
}

// WHY USE auto AT ALL?
// 1. Readability — variable names line up neatly
//    int a{5}; double b{6.7};   vs   auto a{5}; auto b{6.7};
// 2. Forces initialization — auto x; won't compile, catches uninitialized vars
// 3. No silent conversions:
//    std::string_view getString();
//    std::string s1 { getString() };   // BAD: hidden expensive conversion
//    auto        s2 { getString() };   // GOOD: no conversion, exact type

// WHEN TO AVOID auto
// - When you need a specific type different from the initializer
//   auto y { 5 };   // int, but you wanted double — mistake
// - When the type being obvious matters for readability (unsigned, etc.)


// ─────────────────────────────────────────────────────────────
//             TYPE DEDUCTION FOR FUNCTIONS
// ─────────────────────────────────────────────────────────────

// 1. RETURN TYPE DEDUCTION
auto add(int x, int y) {
    return x + y;   // compiler deduces return type as int
}

// ALL return statements must return the SAME type — else compile error
// auto someFcn(bool b) {
//     if (b) return 5;    // int
//     else   return 6.7;  // double  <-- ERROR: mismatched return types
// }

// DOWNSIDE 1 — forward declaration is NOT enough with auto return
// auto foo();          // this declaration is useless to the caller
// you must see the full definition before calling it
// → normal auto-return functions are only callable within the same file

// DOWNSIDE 2 — the prototype hides what type is actually returned
// With objects, you can see the initializer immediately
// With functions, you have to look inside the body — easy to get wrong

// Best practice: prefer explicit return types for functions
// Exception: when return type is complex, fragile, or not important


// 2. TRAILING RETURN SYNTAX — auto used as syntax, NOT deduction
auto multiply(int x, int y) -> int {  // same as: int multiply(int x, int y)
    return x * y;
}

// WHY trailing syntax?
// a) Complex return types are easier to read:
    std::common_type_t<int,double> compare(int, double);        // hard
    auto compare(int, double) -> std::common_type_t<int,double>;// easier

// b) Aligns function names neatly in declarations:
    auto add1(int x, int y)         -> int;
    auto divide(double x, double y) -> double;
    auto printSomething()           -> void;

// c) Required when return type depends on parameter types (decltype uses)
    auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>;
//    (compiler hasn't seen x,y yet at the return type position in normal syntax)


// 3. auto FOR FUNCTION PARAMETERS — does NOT work before C++20
// void addAndPrint(auto x, auto y) { ... }
// In C++20 this compiles BUT it's not type deduction —
// it's actually a FUNCTION TEMPLATE (different feature, covered later)
// Do not confuse the two.


int main() {
    objectTypeDeduction();
    cout << add(3, 4) << "\n";         // 7, return type deduced as int
    cout << multiply(3, 4) << "\n";    // 12, trailing return syntax
    return 0;
}