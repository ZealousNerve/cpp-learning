#include <iostream>
#include <string>
#include <string_view>

// ═══════════════════════════════════════════════════════════════════════════
//  COMPLETE NOTES: std::string  &  std::string_view
//  Covers: declaration, input, length, literals, conversions,
//          function params, return types, constexpr, dangling views
// ═══════════════════════════════════════════════════════════════════════════


// ── HELPER FUNCTIONS (used in demos below) ──────────────────────────────────

void printByValue(std::string str) {
    std::cout << "[copy]   " << str << '\n';
}
void printByView(std::string_view str) {
    std::cout << "[view]   " << str << '\n';
}

std::string buildGreeting(std::string_view name) {
    return "Hello, " + std::string(name) + "!";
    //here we aren't writing s suffix with hello because hello is overloaded with std::string(name), using operator over-
    //-loading
}
std::string_view getLiteral() {
    return "I am a literal — I live forever";
}


int main()
{
    // ═══════════════════════════════════════════════════════════════════════
    //  PART 1 — WHY NOT C-STYLE STRINGS?
    // ═══════════════════════════════════════════════════════════════════════
    //
    //  char name[] = "Alex";   ← fixed size, manual memory, many bugs
    //
    //  C++ gives us two better alternatives:
    //    • std::string       → owns and manages its own memory
    //    • std::string_view  → a lightweight read-only window, owns nothing
    //
    //  Rule of thumb:
    //    Need to store / modify text?  → std::string
    //    Only reading existing text?   → std::string_view


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 2 — std::string  (the owner)
    // ═══════════════════════════════════════════════════════════════════════

    // ── 2.1  Declaration ────────────────────────────────────────────────────
    std::string name { "Alex" };   // list-initialization — preferred in C++
    name = "John";                 // ✅ reassignable
    name += " Doe";                // ✅ appendable
    std::cout << name << '\n';

    // ── 2.2  Strings ≠ Numbers ──────────────────────────────────────────────
    std::string idText { "45" };   // "45" is TEXT, not the integer 45
    // int wrong = idText + 5;     // ❌ won't compile
    int correct = std::stoi(idText) + 5;  // ✅ convert first
    std::cout << "ID + 5 = " << correct << '\n';

    // ── 2.3  Taking Input ───────────────────────────────────────────────────
    //
    //  std::cin >> name
    //    ✅ works for single words
    //    ❌ stops at first whitespace  →  "John Doe" reads only "John"
    //
    //  std::getline(std::cin, name)
    //    ✅ reads the full line including spaces
    //    ❌ BUG: if std::cin was used before, a leftover '\n' sits in
    //       the buffer. getline() reads that empty line and skips your input.
    //
    //  FIX → std::ws  (an INPUT manipulator, like std::setprecision is output)
    //    std::ws discards all leading whitespace (including that '\n')
    //    BEFORE getline reads anything.
    //
    //  CORRECT PATTERN (use this every time):
    //    std::getline(std::cin >> std::ws, name);
    //
    //  ⚠️  std::ws is NOT remembered between calls.
    //      Add it to every single std::getline call.

    // ── 2.4  Length ─────────────────────────────────────────────────────────
    //  .length() returns size_t — an UNSIGNED type.
    //  Storing it in int needs an explicit cast to silence compiler warnings
    //  about signed/unsigned comparison bugs (they are real bugs, not noise).
    int len { static_cast<int>(name.length()) };
    std::cout << "Length: " << len << '\n';

    // ── 2.5  Do NOT pass std::string by value ───────────────────────────────
    //  Every pass-by-value copies the entire string onto the heap → slow.
    //  Solution: use std::string_view for read-only params (see Part 4).


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 3 — std::string_view  (the observer)
    // ═══════════════════════════════════════════════════════════════════════
    //
    //  Mental model:  a camera pointed at a string.
    //  It shows you the picture. It does NOT own the thing it films.
    //  If the thing is destroyed, the camera shows garbage.
    //
    //  Internally it is just two values:
    //    • a pointer to the start of the data
    //    • a length
    //  No heap allocation. No copy. That is why it is cheap.
    //
    //  Introduced in C++17. Lives in <string_view>.

    // ── 3.1  Can point at any kind of string ────────────────────────────────
    std::string_view sv1 { "I am a literal" };  // ✅ literal → static storage, lives forever
    std::string      owned { "I am a string" };
    std::string_view sv2 { owned };             // ✅ points at owned's internal buffer
    std::string_view sv3 { sv2 };              // ✅ view of a view (same pointer, no copy)

    std::cout << sv1 << '\n' << sv2 << '\n' << sv3 << '\n';

    // ── 3.2  Read-only — cannot modify through a view ───────────────────────
    // sv1[0] = 'X';   // ❌ compile error — string_view is read-only

    // ── 3.3  constexpr — string_view wins here ──────────────────────────────
    constexpr std::string_view CONSTANT { "Resolved at compile time" };
    constexpr std::string   BAD{"hello"}; // ❌ not constexpr before C++20
    std::cout << CONSTANT << '\n';


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 4 — CONVERSION RULES
    // ═══════════════════════════════════════════════════════════════════════
    //
    //  string  →  string_view    ✅ implicit  (cheap — just sets a pointer)
    //  string_view → string      ❌ implicit BLOCKED by compiler
    //                            ✅ explicit only  (forces you to see the cost)

    std::string_view sv { "Convert me" };
    std::string_view s  { owned };         // ✅ string → string_view: implicit

    // printByValue(sv);                          // ❌ compile error
    printByValue(std::string { sv });             // ✅ explicit constructor
    printByValue(static_cast<std::string>(sv));   // ✅ explicit cast
    printByView (sv);                             // ✅ no conversion needed
    printByView (owned);                          // ✅ string → string_view: implicit ok


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 5 — THE DANGLING VIEW TRAP (most important safety rule)
    // ═══════════════════════════════════════════════════════════════════════
    //
    //  string_view does NOT keep its target alive.
    //  Two ways to create a dangling view:

    // TRAP 1 — original string is destroyed
    {
        std::string temp { "I am temporary" };
        std::string_view watching { temp };
        std::cout << watching << '\n';   // ✅ fine — temp is alive here
    }
    // std::cout << watching;            // ❌ temp is gone → watching is dangling → UB

    // TRAP 2 — original string is modified (may reallocate its internal buffer)
    std::string mutable_str { "original" };
    std::string_view view_of_it { mutable_str };
    std::cout << view_of_it << '\n';            // ✅ "original"
    mutable_str = "completely new string that is longer and may have reallocated!";
    // std::cout << view_of_it;                 // ❌ buffer may have moved → UB

    // TRAP 3 — returning a view of a local string from a function
    // std::string_view bad() {
    //     std::string local { "dies here" };
    //     return local;   // ❌ local destroyed on return → caller gets dangling view
    // }

    //  GOLDEN RULE:  string_view must NEVER outlive the string it is viewing.
    //  Safe sources for string_view: string literals, function parameters,
    //  or strings guaranteed to outlive the view.


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 6 — LITERAL SUFFIXES
    // ═══════════════════════════════════════════════════════════════════════

    using namespace std::string_literals;       // unlocks  "..."s
    using namespace std::string_view_literals;  // unlocks  "..."sv

    auto a = "foo";    // type: const char*       — C-style, no heap
    auto b = "foo"s;   // type: std::string       — heap allocated, owned
    auto c = "foo"sv;  // type: std::string_view  — no heap, just a view

    // Why the suffix matters:
    // "Hello" + " world"    ❌ can't + two C-style strings
    // "Hello"s + " world"s  ✅ std::string supports +
    std::string joined = "Hello"s + ", " + "world!"s;
    std::cout << joined << '\n';

    std::cout << "no suffix\n";    // const char*
    std::cout << "s suffix\n"s;    // std::string
    std::cout << "sv suffix\n"sv;  // std::string_view


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 7 — FUNCTION PARAMETERS  (the most common decision)
    // ═══════════════════════════════════════════════════════════════════════
    //
    //  ┌───────────────────────┬───────────────────────────────────────────┐
    //  │ std::string_view      │ ✅ DEFAULT — read-only, accepts all types  │
    //  │ const std::string&    │ when caller must pass exactly std::string  │
    //  │ std::string (by value)│ when function needs its own modifiable copy│
    //  └───────────────────────┴───────────────────────────────────────────┘
    //
    //  string_view is the best default for read-only params because it accepts
    //  C-style strings, std::string, and string literals — all without copying.

    printByView("literal");    // ✅
    printByView(owned);        // ✅
    printByView(sv);           // ✅


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 8 — RETURN TYPES
    // ═══════════════════════════════════════════════════════════════════════
    //
    //  ┌───────────────────┬─────────────────────────────────────────────┐
    //  │ std::string       │ returning a built / local string  ✅ safe   │
    //  │ std::string_view  │ returning a literal or sv param   ✅ safe   │
    //  │ std::string_view  │ returning a local std::string     ❌ CRASH  │
    //  └───────────────────┴─────────────────────────────────────────────┘

    std::cout << buildGreeting("Anurag") << '\n';  // ✅ owned, safe
    std::cout << getLiteral()            << '\n';  // ✅ literal, lives forever


    // ═══════════════════════════════════════════════════════════════════════
    //  PART 9 — FULL CHEAT SHEET
    // ═══════════════════════════════════════════════════════════════════════
    //
    //  USE std::string WHEN:
    //    • You need to modify, build, or store text
    //    • Storing user input
    //    • Storing a return value from a function that returns std::string
    //
    //  USE std::string_view WHEN:
    //    • You only need to READ existing text (function params especially)
    //    • You need a constexpr string constant
    //    • You need to view a C-style string or string literal cheaply
    //    • Returning a string literal from a function
    //
    //  ALWAYS REMEMBER:
    //    • Never pass std::string by value unless you need a copy
    //    • Always use std::getline(std::cin >> std::ws, str) for line input
    //    • Cast .length() to int with static_cast<int>() to avoid warnings
    //    • string_view must NEVER outlive the string it points to
    //    • Modifying a std::string invalidates all string_views pointing to it
    //    • string_view may not be null-terminated (don't pass to C functions)
    // ═══════════════════════════════════════════════════════════════════════

    return 0;
}