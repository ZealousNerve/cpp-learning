// ============================================================
//  CHAPTER 11 — FUNCTION OVERLOADING
// ============================================================

#include <iostream>
#include <string_view>

// ─────────────────────────────────────────────────────────────
//  11.1  INTRODUCTION TO FUNCTION OVERLOADING
// ─────────────────────────────────────────────────────────────
// C++ allows multiple functions to share the same name, as long as
// their parameter types (or count) differ. Each such function is
// called an overload. The compiler picks the right one based on the
// arguments you pass — this picking process is called overload resolution.

int    add(int    x, int    y) { return x + y; }   // overload 1
double add(double x, double y) { return x + y; }   // overload 2
int    add(int x, int y, int z){ return x+y+z; }   // overload 3 — different param count

// Return type is NOT used to differentiate overloads.
// The two lines below would cause a compile error if uncommented:
//   int    getVal();
//   double getVal();   // error: only return type differs


// ─────────────────────────────────────────────────────────────
//  11.2  FUNCTION OVERLOAD DIFFERENTIATION
// ─────────────────────────────────────────────────────────────
// What the compiler uses to tell overloads apart:
//   ✔ Number of parameters
//   ✔ Type of parameters
//   ✗ Return type   (not used)
//
// Things that do NOT create distinct types:
//   • typedefs / type aliases     (Age = int  →  same as int)
//   • top-level const on a value  (const int  →  same as int)
//   • ellipsis (...)              counts as its own unique "type"

// These three would all collide — identical after alias resolution:
// typedef int Height;
// void print(int);
// void print(Height);   // NOT a different overload
// void print(const int);// NOT a different overload

// These four ARE distinct because the parameter type lists differ:
void show(int x, double y)   { std::cout << "int,double\n"; }
void show(double x, int y)   { std::cout << "double,int\n"; }
void show(int x, int y)      { std::cout << "int,int\n";    }
void show(double x, double y){ std::cout << "double,double\n"; }

// Name mangling (compiler-internal, FYI):
// The compiler renames functions internally so the linker gets unique
// symbols, e.g. add(int,int) → __add_ii, add(double,double) → __add_dd.
// No standard format — differs per compiler. You never write mangled names.


// ─────────────────────────────────────────────────────────────
//  11.3  OVERLOAD RESOLUTION & AMBIGUOUS MATCHES
// ─────────────────────────────────────────────────────────────
// When you call an overloaded function the compiler runs through these
// steps IN ORDER, stopping as soon as one step finds a single best match.
//
//  Step 1 — Exact match (+ trivial conversions)
//            Trivial: lvalue→rvalue, non-const→const, non-ref→ref.
//            These are still counted as "exact".
//
//  Step 2 — Numeric promotion
//            char/short/bool/float → int or double (widens automatically).
//
//  Step 3 — Numeric conversion
//            Any numeric type → any other numeric type (may narrow/lose data).
//
//  Step 4 — User-defined conversions (e.g. class operator int()).
//
//  Step 5 — Ellipsis (...) match.
//
//  Step 6 — No match found → compile error.
//
// If two or more overloads tie at the SAME step → AMBIGUOUS MATCH → compile error.
// Key: promotion (step 2) always beats conversion (step 3).

void foo(int)    { std::cout << "foo(int)\n";    }
void foo(double) { std::cout << "foo(double)\n"; }

// foo('a')   → char promoted to int   → foo(int)      [step 2]
// foo(4.5f)  → float promoted to double → foo(double) [step 2]
// foo(5L)    → long can convert to int OR double → AMBIGUOUS [step 3 tie]

// Resolving ambiguity:
//   1. Add an exact overload:  void foo(long) {}
//   2. Cast at call site:      foo(static_cast<int>(5L));
//   3. Use a literal suffix:   foo(5u);   // matches foo(unsigned int) if declared

// Multi-argument resolution rule:
// The winning overload must be at-least-as-good for ALL args AND
// strictly better for at least ONE arg. Otherwise → ambiguous.

void printMixed(char c, int n)    { std::cout << "a\n"; }
void printMixed(char c, double d) { std::cout << "b\n"; }
// printMixed('x', 'a'):
//   Both match first param exactly.
//   Second: 'a'→int is promotion vs 'a'→double is conversion.
//   printMixed(char,int) wins because promotion > conversion.


// ─────────────────────────────────────────────────────────────
//  11.4  DELETING FUNCTIONS  (= delete)
// ─────────────────────────────────────────────────────────────
// Sometimes you want to prevent certain argument types from ever matching.
// Mark those overloads as deleted. The compiler then refuses calls to them.
//
// KEY: deleted functions still participate in overload resolution.
//      If a deleted overload is the best match → compile error ("deleted").
//      If it creates a tie → compile error ("ambiguous").
//      "= delete" means "I forbid this", NOT "this doesn't exist".

void printInt(int x) { std::cout << x << '\n'; }
void printInt(char)  = delete;   // block implicit char→int promotion
void printInt(bool)  = delete;   // block implicit bool→int promotion

// printInt(97);    → ok  (exact int match)
// printInt('a');   → compile error: matches deleted printInt(char)
// printInt(true);  → compile error: matches deleted printInt(bool)
// printInt(5.0);   → compile error: AMBIGUOUS (double can go to int OR char OR bool,
//                    none is unambiguously best among the three candidates)

// ── Delete ALL non-exact types at once using a function template ──
// A function template overload is preferred for anything that isn't
// already an exact match for a regular overload.

void strictPrint(int x) { std::cout << x << '\n'; }   // only this is allowed

template <typename T>
void strictPrint(T x) = delete;   // everything else is forbidden

// strictPrint(42);    → ok   (matches regular int overload exactly)
// strictPrint('a');   → compile error: best match is the deleted template
// strictPrint(3.14);  → compile error: same reason


// ─────────────────────────────────────────────────────────────
//  QUICK REFERENCE  — rules to remember
// ─────────────────────────────────────────────────────────────
//  • Overloads differ by: param count OR param types (not return type).
//  • typedef/alias/const-on-value do NOT create new types.
//  • Resolution order: exact > promotion > conversion > user-defined > ellipsis.
//  • Ties at any step → ambiguous match → compile error.
//  • = delete participates in resolution; match → error.
//  • Template overload catches "everything else" when combined with = delete.

int main()
{
    // 11.1 — basic dispatch
    std::cout << add(1, 2)       << '\n';   // add(int,int)    → 3
    std::cout << add(1.2, 3.4)   << '\n';   // add(double,double) → 4.6
    std::cout << add(1, 2, 3)    << '\n';   // add(int,int,int) → 6

    // 11.2 — type differentiation
    show(1, 2.0);    // int,double
    show(2.0, 1);    // double,int

    // 11.3 — resolution steps
    foo('a');         // step 2: char → int promotion
    foo(4.5f);        // step 2: float → double promotion
    // foo(5L);       // step 3 tie → would be AMBIGUOUS (commented to allow compile)

    // 11.4 — delete
    printInt(97);     // ok
    // printInt('a'); // compile error (uncomment to test)

    strictPrint(42);  // ok
    // strictPrint('a'); // compile error (uncomment to test)

    return 0;
}