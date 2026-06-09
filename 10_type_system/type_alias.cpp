#include <iostream>
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair


// "using" creates an alias — just a new NAME for an existing type
// the compiler swaps the alias name with the real type at compile time
// NO new type is created — it's just a nickname

using Distance = double;   // Distance IS double. Not a new type. Just a name.
using Miles    = long;
using Speed    = long;     // both Miles and Speed are just "long" — NOT distinct!

// DANGER: compiler won't stop this — semantically wrong, but compiles fine
// Miles d { 5 };
// Speed s { 3200 };
// d = s;  // works — both are just "long" under the hood
// type aliases are NOT type-safe



// ─── NAMING CONVENTION ────────────────────────────────────────────────────────

// OLD style (C-inherited, avoid):  size_t, nullptr_t       → "_t" suffix
// OLDER nested style:              std::string::size_type  → "_type" suffix
// MODERN C++ (use this):           Capital letter, no suffix → Distance, TestScore



// ─── SCOPE ────────────────────────────────────────────────────────────────────

// alias inside a function → block scope (only usable in that function)
// alias in global namespace / header → file/global scope

// mytypes.h pattern:
// #ifndef MYTYPES_H
// #define MYTYPES_H
//     using Miles = long;
// #endif
// then #include "mytypes.h" wherever needed



// ─── TYPEDEF (old syntax, avoid) ──────────────────────────────────────────────

typedef long Miles2;              // same as: using Miles2 = long;
// typedef int (*FcnType)(double, char);   // hard to read — name buried in middle
// using FcnType = int(*)(double, char);   // easier — name on the left, always



// ─── USE CASE 1: PLATFORM-INDEPENDENT FIXED-WIDTH TYPES ───────────────────────

// int size varies by platform (2 or 4 bytes)
// solution: alias to the right type per platform via preprocessor

// #ifdef INT_2_BYTES
//     using int32_t = long;
// #else
//     using int32_t = int;
// #endif

// this is EXACTLY what <cstdint> does internally
// std::int8_t, std::int16_t, std::int32_t — all just type aliases to char/short/int/long

#include <cstdint>
// std::int8_t is usually alias for signed char → prints as ASCII, NOT number
// int8_t x { 97 };  cout << x → prints 'a', not 97   ← easy to forget, remember this



// ─── USE CASE 2: SIMPLIFY COMPLEX TYPES (best use case) ───────────────────────

using VectPairSI = std::vector<std::pair<std::string, int>>;

bool hasDuplicates(VectPairSI pairlist) { return false; }

// without alias you'd write:
// bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
// everywhere. painful. alias saves you here.



// ─── USE CASE 3: DOCUMENT MEANING OF RETURN TYPE ──────────────────────────────

using TestScore = int;
TestScore gradeTest() { return 95; }  // return type now says WHAT it means, not just "int"
// not always worth it for one function — use a comment instead
// worth it when multiple functions use the same "meaningful" type



// ─── USE CASE 4: EASY TYPE SWAPPING (maintenance) ─────────────────────────────

using StudentId = short;
// later if you need long: just change this one line → whole codebase updates
// using StudentId = long;

// WARNING: changing type family (int → float, signed → unsigned) can break behavior
// always retest if you swap to a different family



// ─── SUMMARY ──────────────────────────────────────────────────────────────────

// using Alias = Type;          → modern, prefer this
// typedef Type Alias;          → old, avoid
// aliases are NOT new types    → no type safety, compiler won't catch mix-ups
// best use: complex types, platform portability, readable return types, easy maintenance
// use judiciously — a bad alias hides familiar types and confuses readers

int main()
{
    Distance d { 3.4 };
    std::cout << d << '\n';  // prints 3.4 — Distance is just double

    VectPairSI list;         // cleaner than writing the full template type
    return 0;
}