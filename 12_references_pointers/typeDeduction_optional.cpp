#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <limits>
#include <functional>


// ════════════════════════════════════════════════════════════
// PART 1 — TYPE DEDUCTION WITH REFERENCES, POINTERS & CONST
// ════════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────────
// 1.1 — RECAP: auto drops const by default
// ─────────────────────────────────────────────────────────────

void recap_const_drop()
{
    const double a { 7.8 };     // type: const double
    auto b { a };               // type: double  ← const DROPPED

    constexpr double c { 7.8 }; // constexpr implicitly applies const
    auto d { c };               // type: double  ← const DROPPED

    const auto e { a };         // type: const double   (reapplied)
    constexpr auto f { c };     // type: constexpr double (reapplied)
    // constexpr is NOT part of the type system — it is never deduced by auto.
    // It must always be explicitly applied.
}


// ─────────────────────────────────────────────────────────────
// 1.2 — auto DROPS REFERENCES
// ─────────────────────────────────────────────────────────────

std::string&       getRef();       // returns std::string&
const std::string& getConstRef();  // returns const std::string&

void auto_drops_references()
{
    auto ref1 { getRef() };   // std::string   (reference dropped)
    auto& ref2 { getRef() };  // std::string&  (dropped, then reapplied)

    // With const std::string& return:
    // Step 1: drop reference  → const std::string   (low-level const becomes top-level)
    // Step 2: drop top-level const → std::string
    auto ref3 { getConstRef() };        // std::string

    const auto ref4 { getConstRef() };  // const std::string  (dropped, reapplied)

    auto& ref5 { getConstRef() };       // const std::string&
    // Reference is reapplied, NOT dropped → type stays const std::string&
    // const here is LOW-LEVEL (on the referenced object) → never dropped

    const auto& ref6 { getConstRef() }; // const std::string&  (same result, but EXPLICIT)
    // ref6 and ref5 are identical. Always prefer ref6's style — makes intent clear.
}

// ╔══════════════════════════════════════════════════════════════╗
// ║  TOP-LEVEL vs LOW-LEVEL CONST                                ║
// ║                                                              ║
// ║  Top-level  → applies to the object ITSELF                   ║
// ║    const int x;       ← x itself is const                    ║
// ║    int* const ptr;    ← ptr itself is const                  ║
// ║                                                              ║
// ║  Low-level  → applies to the object REFERENCED or POINTED TO ║
// ║    const int& ref;    ← referenced object is const           ║
// ║    const int* ptr;    ← pointed-to object is const           ║
// ║                                                              ║
// ║  Type deduction ONLY drops top-level const.                  ║
// ║  Low-level const is ALWAYS preserved.                        ║
// ║                                                              ║
// ║  GOTCHA: Dropping a reference from const T& converts         ║
// ║  its low-level const into top-level const — which then       ║
// ║  also gets dropped. const std::string& → drop ref →          ║
// ║  const std::string (now top-level) → also dropped.           ║
// ╚══════════════════════════════════════════════════════════════╝


// ─────────────────────────────────────────────────────────────
// 1.3 — constexpr REFERENCES
// ─────────────────────────────────────────────────────────────

constexpr std::string_view hello { "Hello" }; // implicitly const

constexpr const std::string_view& getConstexprRef()
{
    return hello;
}

void constexpr_deduction()
{
    auto ref1 { getConstexprRef() };
    // drop ref → const std::string_view (top-level) → drop → std::string_view

    constexpr auto ref2 { getConstexprRef() };
    // same steps, constexpr applied explicitly → constexpr const std::string_view
    // (constexpr implicitly adds const)

    auto& ref3 { getConstexprRef() };
    // ref reapplied → not dropped → const std::string_view& (low-level, not dropped)

    constexpr const auto& ref4 { getConstexprRef() };
    // ref reapplied, low-level const kept, constexpr applied → constexpr const std::string_view&
}


// ─────────────────────────────────────────────────────────────
// 1.4 — auto DOES NOT DROP POINTERS
// ─────────────────────────────────────────────────────────────

std::string* getPtr();

void auto_and_pointers()
{
    auto  ptr1 { getPtr() };  // std::string*  (pointer kept)
    auto* ptr2 { getPtr() };  // std::string*  (same result, explicit intent)

    // WHY prefer auto*?
    // 1. Makes it visually clear you're deducing a pointer type.
    // 2. Compiler errors if initializer is not a pointer (safety net).
    // 3. Gives explicit control over where const goes (see 1.5).
}


// ─────────────────────────────────────────────────────────────
// 1.5 — auto vs auto* — the real difference
// ─────────────────────────────────────────────────────────────

void auto_vs_auto_star()
{
    // auto  → deduces the full pointer type (std::string* is what auto becomes)
    // auto* → deduces the base type (std::string), then * is reapplied after

    auto  ptr3 { *getPtr() };  // std::string  (dereferenced → value, not pointer)
    // auto* ptr4 { *getPtr() }; // COMPILE ERROR — initializer is not a pointer,
                                  // but auto* enforces that the deduced type must be one
}


// ─────────────────────────────────────────────────────────────
// 1.6 — const + POINTERS — the full matrix
// ─────────────────────────────────────────────────────────────

// Mnemonic before diving in:
//   int* const   = const POINTER (to int)   → auto* const   = const pointer
//   const int*   = pointer TO CONST (int)   → const auto*   = pointer to const

void const_pointers()
{
    // ── Case A: initializer is std::string* ─────────────────
    {
        const auto  ptr1 { getPtr() };  // std::string* const   (const pointer)
        auto const  ptr2 { getPtr() };  // std::string* const   (same — order irrelevant)

        const auto* ptr3 { getPtr() };  // const std::string*   (pointer to const)
        auto* const ptr4 { getPtr() };  // std::string* const   (const pointer)
    }

    // ── Case B: initializer is const std::string* const ─────
    {
        std::string s{};
        const std::string* const ptr { &s };

        auto  ptr1 { ptr };  // const std::string*        top-level const dropped, low-level kept
        auto* ptr2 { ptr };  // const std::string*        same

        auto const  ptr3 { ptr };  // const std::string* const   dropped, reapplied
        const auto  ptr4 { ptr };  // const std::string* const   same

        auto* const ptr5 { ptr };  // const std::string* const   auto* const reapplies top-level
        const auto* ptr6 { ptr };  // const std::string*         const auto* applies low-level

        // const auto const ptr7 { ptr }; // COMPILE ERROR — const applied twice

        const auto* const ptr8 { ptr }; // const std::string* const  (most explicit — preferred)
    }
}


// ─────────────────────────────────────────────────────────────
// 1.7 — WHY references drop but pointers don't
// ─────────────────────────────────────────────────────────────

// A reference IS the object — it's a transparent alias. Evaluating a reference
// gives you the object's value directly. So deducing "the type of this expression"
// naturally yields the object's type, not a reference. You re-add & with auto&.

// A pointer HOLDS AN ADDRESS — it is its own distinct object.
// Evaluating a pointer gives you the pointer, not what it points to
// (you dereference explicitly with * to get the value).
// So deducing a pointer expression gives you the pointer type.


// ─────────────────────────────────────────────────────────────
// 1.8 — DEDUCTION RULES CHEAT SHEET
// ─────────────────────────────────────────────────────────────

// Step 1: If initializer is a reference → drop it (unless you used auto&).
//         For const T& : dropping the ref makes const top-level → also dropped.
// Step 2: Drop top-level const. Low-level const (through ptr/ref) is kept.
// Step 3: Pointers are never dropped.
// Step 4: constexpr is never deduced — always apply explicitly.
// Step 5: Reapply anything you need:
//           const auto       → top-level const
//           const auto&      → const reference
//           auto* const      → const pointer
//           const auto*      → pointer to const
//           const auto* const → const pointer to const


// ─────────────────────────────────────────────────────────────
// 1.9 — BEST PRACTICES (Part 1)
// ─────────────────────────────────────────────────────────────

// → Always use const auto& for const references, even when redundant.
// → Always use auto* over auto when deducing pointers.
// → Always explicitly reapply const/constexpr for clarity.


// ════════════════════════════════════════════════════════════
// PART 2 — std::optional  (C++17)
// ════════════════════════════════════════════════════════════
// std::optional<T> is either "a value of type T" or "nothing."
// Both states are explicit and unambiguous.
// Think of it as a container that holds 0 or 1 items.
// ════════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────────
// 2.1 — THE PROBLEM: why sentinel values fail
// ─────────────────────────────────────────────────────────────

// Consider a function that divides two ints. If y == 0, it cannot return.
// Every integer (including the error sentinel) is a valid division result.

int doIntDivision_sentinel(int x, int y)
{
    if (y == 0)
        return std::numeric_limits<int>::lowest(); // "magic" error value
    return x / y;
}
// SEMIPREDICATE PROBLEM:
// doIntDivision_sentinel(std::numeric_limits<int>::lowest(), 1)
// returns std::numeric_limits<int>::lowest() — success or failure? Indistinguishable.

// Other downsides of sentinels:
// → Caller must know which value signals an error (differs per function).
// → No value exists that can safely mean "error" for all possible inputs.
// → Code that forgets to check the sentinel silently uses a wrong value.


// ─────────────────────────────────────────────────────────────
// 2.2 — RETURNING std::optional — the clean solution
// ─────────────────────────────────────────────────────────────

std::optional<int> doIntDivision(int x, int y)
{
    if (y == 0)
        return {};        // no value — equivalent to: return std::nullopt;
    return x / y;         // int is implicitly wrapped into std::optional<int>
}

void example_return()
{
    std::optional<int> result1 { doIntDivision(20, 5) };
    if (result1)                         // implicit bool: true if has value
        std::cout << *result1 << '\n';   // dereference to extract value
    else
        std::cout << "failed\n";

    std::optional<int> result2 { doIntDivision(5, 0) };
    if (result2)
        std::cout << *result2 << '\n';
    else
        std::cout << "failed\n";
    // Output:
    // 4
    // failed
}


// ─────────────────────────────────────────────────────────────
// 2.3 — CONSTRUCTION
// ─────────────────────────────────────────────────────────────

void construction_examples()
{
    std::optional<int> o1 { 5 };            // has value: 5
    std::optional<int> o2 {};               // no value
    std::optional<int> o3 { std::nullopt }; // no value (explicit, same as o2)
    // std::nullopt — special constant meaning "no value", like nullptr for pointers
}


// ─────────────────────────────────────────────────────────────
// 2.4 — ACCESSING THE VALUE — three methods
// ─────────────────────────────────────────────────────────────

void access_examples()
{
    std::optional<int> o1 { 42 };
    std::optional<int> o2 {};

    // Method 1: operator*  (dereference)
    std::cout << *o1;    // 42
    // std::cout << *o2; // UNDEFINED BEHAVIOR if no value — same danger as dereferencing nullptr

    // Method 2: .value()
    std::cout << o1.value();  // 42
    // o2.value();             // throws std::bad_optional_access if no value (safer than *, but slower)

    // Method 3: .value_or(fallback)
    std::cout << o2.value_or(0);  // 0  (fallback, no exception, no UB)
    std::cout << o1.value_or(0);  // 42 (has value, fallback ignored)

    // Checking before access:
    if (o1.has_value()) std::cout << *o1;  // explicit check
    if (o1)             std::cout << *o1;  // implicit bool — preferred (cleaner syntax)
}


// ─────────────────────────────────────────────────────────────
// 2.5 — std::optional vs POINTER — comparison
// ─────────────────────────────────────────────────────────────

// ┌──────────────────────┬──────────────────────┬─────────────────────────────┐
// │ Behavior             │ Pointer              │ std::optional               │
// ├──────────────────────┼──────────────────────┼─────────────────────────────┤
// │ No value             │ = nullptr / {}       │ = {} / std::nullopt         │
// │ Has value            │ = &someVar           │ = someValue                 │
// │ Check                │ if (ptr)             │ if (opt) / .has_value()     │
// │ Get value            │ *ptr                 │ *opt / .value()             │
// │ With fallback        │ manual ternary       │ .value_or(fallback)         │
// │ Semantics            │ REFERENCE (alias)    │ VALUE (owns a copy)         │
// │ Assignment copies    │ the pointer          │ the contained value         │
// │ Return local safely? │ NO (dangling ptr)    │ YES (copy returned safely)  │
// └──────────────────────┴──────────────────────┴─────────────────────────────┘

// The critical semantic difference:
// Pointer → reference semantics. Points to something that lives elsewhere.
//           Returning a pointer to a local variable = dangling pointer (UB).
//
// std::optional → value semantics. OWNS its value like a small container.
//                 Returning std::optional by value copies the value safely to the caller.


// ─────────────────────────────────────────────────────────────
// 2.6 — std::optional AS OPTIONAL FUNCTION PARAMETER
// ─────────────────────────────────────────────────────────────

// Before std::optional, "optional argument" meant a nullable pointer:
void printID_ptr(const int* id = nullptr)
{
    if (id) std::cout << "ID: " << *id << '\n';
    else    std::cout << "ID unknown\n";
    // Limitation: caller must pass an lvalue address — can't do printID_ptr(34)
}

// With std::optional:
void printID_opt(std::optional<const int> id = std::nullopt)
{
    if (id) std::cout << "ID: " << *id << '\n';
    else    std::cout << "ID unknown\n";
}

void optional_param_usage()
{
    printID_opt();       // no argument
    int userid { 34 };
    printID_opt(userid); // lvalue works
    printID_opt(62);     // rvalue works too — std::optional copies it
}

// LIMITATION: std::optional<T> copies T on construction.
// For expensive-to-copy types (std::string, large structs), this is wasteful.
// std::optional does NOT support references directly (as of C++23).

// PREFERRED ALTERNATIVES for expensive types:

struct Employee { std::string name{}; int id{}; };

// Option 1 — Function overloading (cleanest and most readable):
void printEmployeeID()
{
    std::cout << "ID unknown\n";
}
void printEmployeeID(const Employee& e)   // no copy — passed by const ref
{
    std::cout << "ID: " << e.id << '\n';
}
// printEmployeeID();              — no employee
// printEmployeeID(emp);           — lvalue
// printEmployeeID({"Bob", 5});    — rvalue (works with overloading)

// Option 2 — const T* (simpler, familiar):
void printEmployeeID_ptr(const Employee* e = nullptr)
{
    if (e) std::cout << "ID: " << e->id << '\n';
    else   std::cout << "ID unknown\n";
}

// Option 3 — std::optional<std::reference_wrapper<T>> (avoid unless necessary):
// Verbose, unreadable. Covered in chapter 17.5. Not worth it here.


// ─────────────────────────────────────────────────────────────
// 2.7 — PROS, CONS, AND WHEN TO USE
// ─────────────────────────────────────────────────────────────

// ✅ PROS:
//   1. Self-documenting return type — callers know "this might be empty."
//   2. No sentinel needed — no magic number to remember or misuse.
//   3. No semipredicate problem — success/failure is always unambiguous.
//   4. .value_or() gives a clean fallback without branching.
//   5. Rvalues work fine as optional parameters (copy is made safely).

// ❌ CONS:
//   1. Must check before dereferencing — empty optional + * = UB.
//   2. Cannot communicate WHY it failed — only that it did.
//   3. Copies the value — bad for large/expensive types.

// WHEN TO USE:
//   ✅ Fallible function where all possible values are valid (no sentinel possible).
//   ✅ Search/lookup operations — "find this or nothing."
//   ✅ Optional parameters when T is cheap to copy.
//   ❌ When callers need to know WHY it failed → use std::expected (C++23)
//      or exceptions instead.

// std::expected<T, E> (C++23) — brief forward note:
//   The "failure" case carries an error value (error code, message, enum).
//   Use it when the reason for failure matters to the caller, not just the fact of failure.


// ─────────────────────────────────────────────────────────────
// 2.8 — BEST PRACTICES (Part 2)
// ─────────────────────────────────────────────────────────────

// Return type:
//   → Prefer std::optional<T> over sentinel values for fallible functions.
//   → Use std::expected<T,E> (C++23) if failure reason matters.

// Optional parameters:
//   → Prefer function overloading (most readable, no copy cost).
//   → Use std::optional<T> when T is cheap to copy and overloading is awkward.
//   → Use const T* when T is expensive to copy.
//   → Avoid std::optional<std::reference_wrapper<T>> in practice.


int main()
{
    example_return();
    construction_examples();
    access_examples();
    optional_param_usage();
    return 0;
}