/**
 * TOPIC  : Variable Initialization, All 5 Forms + Narrowing Rules
 * CHAPTER: 1.4, Variable assignment and initialization
 * SOURCE : https://learncpp.com/cpp-tutorial/variable-assignment-and-initialization/
 *
 * KEY INSIGHT: How you initialize a variable isn't just style, it changes
 *              what the compiler will and won't allow. List-initialization {}
 *              is strictly superior for most cases because it catches
 *              narrowing conversions that the other forms silently swallow.
 */

// ── PART 1: The 5 Initialization Forms ────────────────────────────────────

int a;          // default-initialization  → value is INDETERMINATE (undefined behavior to read!)
int b = 5;      // copy-initialization     → initial value after equals sign
int c (6);      // direct-initialization   → initial value in parentheses
int d { 7 };    // direct-list-initialization (preferred) → value in braces
int e {};       // value-initialization    → empty braces, always initializes to 0 for ints

// As of C++17: copy, direct, and list initialization behave identically
// in MOST cases. The critical exception is narrowing conversions (see Part 2).

// ── PART 2: The Narrowing Conversion Difference ───────────────────────────
//
// A narrowing conversion loses information, like fitting 4.5 into an int.
// The three forms handle this very differently:

// int w1 { 4.5 };  // ❌ COMPILE ERROR, list-init REFUSES narrowing conversions
// int w2 = 4.5;    // ✅ compiles, but w2 = 4 (fractional part silently lost)
// int w3 (4.5);    // ✅ compiles, but w3 = 4 (fractional part silently lost)

// LESSON: List-initialization acts as a compile-time safety net.
// The other two forms let you shoot yourself in the foot silently.
// Use {} for new code.


// ── PART 3: When Each Form Is Used Beyond Declarations ────────────────────
//
// Copy-initialization is also triggered implicitly by:
//   - Passing arguments to a function by value: foo(x) copies x
//   - Returning from a function by value: return x copies x
//   - Catching exceptions by value: catch (MyException e)
//
// Direct-initialization is also triggered by:
//   - Explicit casts: static_cast<int>(4.5)

// ── PART 4: The Two Flavors of List-Initialization ────────────────────────

int width { 5 };       // direct-list-initialization (PREFERRED)
int height = { 6 };    // copy-list-initialization (rarely needed, just use the above)

// Both are "list initialization", both catch narrowing conversions.
// The direct form (without =) is universally preferred.


// ── PART 5: Value-Initialization and the Zero Rule ────────────────────────
//
// Empty braces {} trigger "value-initialization."
// For fundamental types (int, double, bool, char, pointer):
//   Value-initialization → zero-initialization → the value is 0 (or equivalent)
//
// This is guaranteed by the standard, not compiler-specific behavior.

int zero_int {};        // guaranteed 0
double zero_double {};  // guaranteed 0.0
bool zero_bool {};      // guaranteed false
int* zero_ptr {};       // guaranteed nullptr


// ── PART 6: List-Initialization for Multi-Value Types ─────────────────────
//
// The name "list-initialization" comes from its ability to initialize
// objects with a LIST of values, not just a single value.
// Vectors, arrays, and structs all benefit from this syntax.
//
// Example (you'll understand this fully by Chapter 16):
//   std::vector<int> primes { 2, 3, 5, 7, 11 };  // initialized from a list


int main()
{
    // THE RULE TO FOLLOW:
    // For new code, use direct-list-initialization {} for everything.
    // Exception: when you intentionally want copy or direct init semantics
    // (rare in practice, you'll know when you need it).

    int x {};           // value-initialized to 0
    int y { 42 };       // direct-list-initialized to 42

    // ALWAYS initialize. An uninitialized variable is undefined behavior.
    // The compiler might give you 0, garbage, or something that changes each run.

    return 0;
}
