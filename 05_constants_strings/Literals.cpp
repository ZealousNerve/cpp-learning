#include <iostream>

void why_suffixes_matter()
{
    // ❌ DANGEROUS: 3000000000 overflows int (max int is ~2.1 billion)
    // long a = 3000000000;    // compiler sees the literal as int FIRST → UB

    // ✅ SAFE: suffix tells compiler "treat this as long directly"
    long a = 3000000000L;

    // ❌ SILENT BUG: mixing signed/unsigned in arithmetic
    unsigned int x = 4294967295u; // max value of unsigned int
    // auto result = x + 1;        // if '1' is treated as int → potential UB

    // ✅ SAFE: both operands are unsigned → defined wraparound to 0
    auto result = x + 1u;

    std::cout << "a  = " << a      << '\n';
    std::cout << "x  = " << x      << '\n';
    std::cout << "x+1= " << result << '\n';
}


// ────────────────────────────────────────────────────────────
//  SECTION 2: NUMERIC LITERAL SUFFIXES (Reference Table)
//
//  Suffix        | Type
//  ──────────────|──────────────────────────
//  (none)        | int
//  u / U         | unsigned int
//  l / L         | long
//  ul / UL       | unsigned long
//  ll / LL       | long long
//  ull / ULL     | unsigned long long
//  f / F         | float
//  (none for fp) | double
//  l / L (fp)    | long double
//  z / Z (C++23) | signed std::size_t
//  uz / UZ(C++23)| std::size_t
//
//  Rules:
//  - Two consecutive 'l' or 'L' must be SAME case (lL is invalid)
//  - 's' and 'sv' (string suffixes) must be LOWERCASE
// ────────────────────────────────────────────────────────────

void numeric_suffix_examples()
{
    std::cout << "\n-- Numeric Suffixes --\n";
    std::cout << sizeof(5)    << '\n'; // int        → typically 4 bytes
    std::cout << sizeof(5u)   << '\n'; // unsigned   → typically 4 bytes
    std::cout << sizeof(5L)   << '\n'; // long       → typically 8 bytes (platform-dependent)
    std::cout << sizeof(5LL)  << '\n'; // long long  → typically 8 bytes
    std::cout << sizeof(5.0)  << '\n'; // double     → typically 8 bytes
    std::cout << sizeof(5.0f) << '\n'; // float      → typically 4 bytes

    // MENTAL CHECK: Run this, reason before looking.
    // Why does 5L and 5LL sometimes print the same size?
    // Answer: on most 64-bit systems, long and long long are both 8 bytes.
    // On 32-bit systems, long is 4 bytes and long long is 8 bytes.
}


// ────────────────────────────────────────────────────────────
//  SECTION 3: auto + SUFFIX (Important for STL and templates)
//
//  When you use 'auto', the type is DEDUCED from the literal.
//  Suffixes directly control what type 'auto' picks.
//  You WILL need this when working with STL containers.
// ────────────────────────────────────────────────────────────

void auto_with_suffixes()
{
    std::cout << "\n-- auto + Suffix --\n";

    auto a = 5;      // int
    auto b = 5u;     // unsigned int
    auto c = 5L;     // long
    auto d = 5LL;    // long long
    auto e = 5.0;    // double
    auto f = 5.0f;   // float

    // Why this matters in real code:
    // for (auto i = 0; i < vec.size(); ++i)   ← 'i' is int, vec.size() is size_t
    //                                            → signed/unsigned comparison warning
    //
    // for (auto i = 0u; i < vec.size(); ++i)  ← both unsigned → no warning ✅

    std::cout << "a (int)    = " << a << '\n';
    std::cout << "b (uint)   = " << b << '\n';
    std::cout << "e (double) = " << e << '\n';
    std::cout << "f (float)  = " << f << '\n';
}


// ────────────────────────────────────────────────────────────
//  SECTION 4: STRING LITERALS — C-style vs Modern C++
//
//  This matters for Jarvis: every voice command, every string
//  you pass to an LLM API, every system command — they're strings.
//  Knowing which type to use is a real performance decision.
// ────────────────────────────────────────────────────────────

#include <string>
#include <string_view>

using namespace std::string_literals;       // enables "..."s
using namespace std::string_view_literals;  // enables "..."sv

void string_literals_demo()
{
    std::cout << "\n-- String Literals --\n";

    // Type 1: C-style string (const char*)
    // - Raw pointer to a char array
    // - Null-terminated ('\0' appended automatically)
    // - Lives for the entire program duration (static storage)
    // - AVOID in modern C++ unless interfacing with C APIs
    auto s1 = "hello";         // const char*

    // Type 2: std::string (suffix: s)
    // - Full object, owns its memory, safe, resizable
    // - Use when you need to MODIFY the string
    auto s2 = "hello"s;        // std::string

    // Type 3: std::string_view (suffix: sv)
    // - Read-only view into an existing string (no copy, no allocation)
    // - Use when you only need to READ — fastest option
    // - DANGER: the original string must outlive the view
    auto s3 = "hello"sv;       // std::string_view

    std::cout << "C-style  : " << s1 << '\n';
    std::cout << "string   : " << s2 << '\n';
    std::cout << "sv       : " << s3 << '\n';

    // QUICK DECISION RULE:
    // Reading only?              → string_view (sv)
    // Need to modify/build?      → string (s)
    // Calling C API (printf etc) → const char* (no suffix)
}


// ────────────────────────────────────────────────────────────
//  SECTION 5: MAGIC NUMBERS — What they are, why avoid them
//
//  A magic number is a raw literal with no explanation.
//  Makes code unreadable and hard to maintain.
// ────────────────────────────────────────────────────────────

void magic_number_demo()
{
    std::cout << "\n-- Magic Numbers --\n";

    // ❌ BAD: What does 86400 mean? No one knows without context.
    int seconds_in_day_bad = 86400;

    // ✅ GOOD: Self-documenting
    constexpr int SECONDS_PER_MINUTE = 60;
    constexpr int MINUTES_PER_HOUR   = 60;
    constexpr int HOURS_PER_DAY      = 24;
    constexpr int SECONDS_PER_DAY    = SECONDS_PER_MINUTE * MINUTES_PER_HOUR * HOURS_PER_DAY;

    std::cout << "Seconds in a day: " << SECONDS_PER_DAY << '\n';

    // Rule: If you see a raw number in code and ask "what is this?" — it's a magic number.
    // Replace it with a named constexpr.
}


// ────────────────────────────────────────────────────────────
//  SECTION 6: DIGIT SEPARATORS (C++14)
//
//  Use ' (single quote) to group digits visually.
//  The compiler ignores them — purely for readability.
// ────────────────────────────────────────────────────────────

void digit_separator_demo()
{
    std::cout << "\n-- Digit Separators --\n";

    long   big_decimal  = 2'132'673'462;   // easier to read than 2132673462
    int    binary_val   = 0b1011'0010;     // binary grouped in nibbles (4 bits)
    int    hex_val      = 0xFF'AA'BB;      // hex grouped in bytes

    std::cout << "Decimal  : " << big_decimal  << '\n';
    std::cout << "Binary   : " << binary_val   << '\n';
    std::cout << "Hex      : " << hex_val      << '\n';
}


// ────────────────────────────────────────────────────────────
//  SECTION 7: OUTPUT IN DIFFERENT BASES
//
//  std::hex / std::oct / std::dec are "sticky" — they stay
//  active until you explicitly change them.
//  This is a common source of bugs — always reset to dec.
// ────────────────────────────────────────────────────────────

void base_output_demo()
{
    std::cout << "\n-- Base Output --\n";

    int x = 255;
    std::cout << std::dec << x << '\n';  // 255   (decimal)
    std::cout << std::hex << x << '\n';  // ff    (hexadecimal)
    std::cout << x        << '\n';       // ff    ← STICKY! still hex
    std::cout << std::oct << x << '\n';  // 377   (octal)
    std::cout << std::dec << x << '\n';  // 255   (reset to decimal)

    // KEY LESSON: std::hex persists. Always reset with std::dec when done.
}


// ────────────────────────────────────────────────────────────
//  SECTION 8: BINARY OUTPUT — Three Methods
//
//  Method 1: std::bitset  (C++11, always available)
//  Method 2: std::format  (C++20, modern preferred)
//  Method 3: std::println (C++23, cleanest)
// ────────────────────────────────────────────────────────────

#include <bitset>
#include <format>   // C++20 — needs compiler support
// #include <print> // C++23 — uncomment if your compiler supports it

void binary_output_demo()
{
    std::cout << "\n-- Binary Output --\n";

    int val = 0b1100'0101; // 197 in decimal

    // Method 1: std::bitset — specify how many bits to display
    std::cout << std::bitset<8>{ val } << '\n';  // 11000101
    std::cout << std::bitset<4>{ 0b1010 } << '\n'; // 1010 (temporary object)

    // The temporary object trick:
    // std::bitset<4>{ 0b1010 } creates an unnamed bitset
    // prints it, then destroys it — no variable needed.
    // You'll see this pattern a lot in modern C++.

    // Method 2: std::format (C++20) — more flexible
    std::cout << std::format("{:b}\n",  val);    // 11000101 (no prefix)
    std::cout << std::format("{:#b}\n", val);    // 0b11000101 (with 0b prefix)
    std::cout << std::format("{:08b}\n", val);   // 11000101 (zero-padded to 8 digits)

    // Method 3: std::println — C++23, cleanest syntax
    // std::println("{:b} {:#b}", val, val);  // uncomment for C++23
}


// ────────────────────────────────────────────────────────────
//  MAIN — runs all sections in order
// ────────────────────────────────────────────────────────────

int main()
{
    why_suffixes_matter();
    numeric_suffix_examples();
    auto_with_suffixes();
    string_literals_demo();
    magic_number_demo();
    digit_separator_demo();
    base_output_demo();
    binary_output_demo();

    return 0;
}


// ────────────────────────────────────────────────────────────
//  MENTAL CHECK (answer before running):
//
//  Q1: What does this print?
//      std::cout << sizeof(5) << sizeof(5L) << sizeof(5LL);
//      → Think: int, long, long long. Size depends on platform.
//
//  Q2: What type is 'x' here?
//      auto x = "Jarvis"sv;
//      → std::string_view
//
//  Q3: Is this safe? Why or why not?
//      std::string_view sv = "hello"s;
//      → Technically unsafe: the "hello"s temporary is destroyed
//        after the line, leaving sv dangling. Use string, not sv here.
//
//  Q4: What does std::hex do to SUBSEQUENT outputs?
//      → It's sticky — stays hex until you explicitly use std::dec.
// ────────────────────────────────────────────────────────────