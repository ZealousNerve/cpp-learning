// ============================================================
// TOPIC: Inline Functions and Inline Variables (C++17)
// ============================================================


// ─────────────────────────────────────────────────────────────
// SECTION 1 — WHY FUNCTIONS HAVE OVERHEAD
// ─────────────────────────────────────────────────────────────

// Every function call has "overhead" — extra work the CPU must do
// that has NOTHING to do with the actual logic of the function.

// What happens during a normal function call:
//   1. CPU saves the current instruction address (to know where to return)
//   2. CPU saves current register values (to restore later)
//   3. Parameters are instantiated and initialized
//   4. Execution jumps to the function body
//   5. After function ends, execution jumps back
//   6. Return value is copied out

// For LARGE functions → overhead is negligible compared to run time.
// For SMALL functions (e.g., returning a single expression) →
//     overhead can be LARGER than the actual work being done.
//     If called in a loop = serious performance penalty.

int min_normal(int x, int y)
{
    return (x < y) ? x : y;  // tiny body — calling this 1M times? overhead matters.
}


// ─────────────────────────────────────────────────────────────
// SECTION 2 — INLINE EXPANSION (the compiler's trick)
// ─────────────────────────────────────────────────────────────

// The compiler can REPLACE a function call with the actual body of the function.
// This is called "inline expansion."

// BEFORE expansion (what you write):
//   std::cout << min_normal(5, 6) << '\n';

// AFTER expansion (what the compiler generates):
//   std::cout << ((5 < 6) ? 5 : 6) << '\n';

// Benefits of inline expansion:
//   ✅ Eliminates call overhead entirely
//   ✅ Enables further optimizations — e.g., the compiler now sees a
//      constant expression and can fold it to:
//      std::cout << 5 << '\n';   ← computed at compile time!

// Cost of inline expansion:
//   ❌ Each expansion copies the function body into the call site.
//      If the function is large and called many times → binary grows larger.
//      Larger binary → worse cache performance → can actually SLOW things down.

// When is inline expansion beneficial?
//   ✅ Small, simple functions (a few statements max)
//   ✅ Functions called repeatedly (especially inside loops)
//   ❌ Large or complex functions — overhead is tiny vs. runtime; don't expand


// ─────────────────────────────────────────────────────────────
// SECTION 3 — WHO DECIDES? THE COMPILER.
// ─────────────────────────────────────────────────────────────

// Every function is either:
//   (a) "May be expanded" — most functions fall here.
//       Compiler evaluates EACH call site individually and decides.
//       It might expand: none, some, or all calls.
//   (b) "Cannot be expanded" — most common case: function defined
//       in a DIFFERENT translation unit. Compiler doesn't see the
//       body, so it has nothing to substitute.

// KEY INSIGHT: Modern compilers are better at deciding inline expansion
// than humans. Trust the compiler. Don't second-guess it.


// ─────────────────────────────────────────────────────────────
// SECTION 4 — THE `inline` KEYWORD: HISTORICAL MEANING (OBSOLETE USE)
// ─────────────────────────────────────────────────────────────

// Originally, `inline` was a HINT to the compiler:
//   "Hey, please consider expanding this function inline."

inline int min_hint(int x, int y)  // ← old-school use
{
    return (x < y) ? x : y;
}

// WHY THIS IS OBSOLETE NOW — 4 reasons:
//   1. It's premature optimization. Misuse can HURT performance.
//   2. Compiler is FREE to ignore the hint entirely.
//   3. Wrong granularity — `inline` is on the function definition,
//      but expansion decisions are made per call site. One keyword
//      can't capture that nuance.
//   4. Modern compilers are smarter than us at this. They will ignore
//      or devalue your inline hint anyway.

// ⚠️ BEST PRACTICE: Do NOT use `inline` to request inline expansion.


// ─────────────────────────────────────────────────────────────
// SECTION 5 — THE `inline` KEYWORD: MODERN MEANING (IMPORTANT)
// ─────────────────────────────────────────────────────────────

// Modern C++ redefined what `inline` ACTUALLY means:
//   "This identifier is allowed to be DEFINED in MULTIPLE translation units."

// This is its primary use today — an ODR (One Definition Rule) exemption.

// ── RECAP: The ODR problem ──────────────────────────────────
// Normal rule: a function can only be DEFINED once across the entire program.
// If you put a non-inline function definition in a .h file and include it
// in multiple .cpp files → each .cpp gets its own copy of that definition
// → linker sees duplicate definitions → LINKER ERROR.

// ── How `inline` fixes it ────────────────────────────────────
// Marking a function `inline` tells the linker:
//   "All these definitions are the same function — deduplicate them."
// The linker collapses all copies into ONE. No ODR violation.

// Requirements for an inline function:
//   1. The compiler must see the FULL definition (not just a declaration)
//      in EVERY translation unit where the function is used.
//      → A forward declaration alone is NOT enough.
//   2. Only ONE definition per translation unit (duplicates within the
//      same .cpp = compile error).
//   3. ALL definitions across all translation units must be IDENTICAL.
//      → Even a tiny difference = undefined behavior (UB). No warning.

// ── Example without header ───────────────────────────────────
// main.cpp and math.cpp BOTH define pi() marked inline — this is FINE:

//   // main.cpp
//   inline double pi() { return 3.14159; }
//
//   // math.cpp
//   inline double pi() { return 3.14159; }   ← identical, so OK

// Remove `inline` from both → linker error (ODR violation).


// ─────────────────────────────────────────────────────────────
// SECTION 6 — INLINE FUNCTIONS IN HEADER FILES (THE STANDARD PATTERN)
// ─────────────────────────────────────────────────────────────

// Inline functions belong in HEADER files. Here's why:
//   - Including the header into any .cpp automatically gives that
//     translation unit the full definition (satisfying requirement #1).
//   - Since all .cpp files include the same header, all definitions
//     are identical (satisfying requirement #3).
//   - The linker deduplicates them (satisfying ODR).

// pi.h
// ─────
// #ifndef PI_H
// #define PI_H
//
// inline double pi() { return 3.14159; }
//
// #endif

// main.cpp → #include "pi.h"   → has pi() definition
// math.cpp → #include "pi.h"   → also has pi() definition
// Linker → sees both → deduplicates → ONE pi() in final binary. ✅


// ─────────────────────────────────────────────────────────────
// SECTION 7 — WHY NOT JUST MAKE EVERYTHING INLINE IN HEADERS?
// ─────────────────────────────────────────────────────────────

// Two real costs:

// COST 1 — Compile time:
//   An inline function included in 6 .cpp files is COMPILED 6 TIMES
//   (before the linker removes duplicates).
//   A regular function in a .cpp is compiled ONCE.
//   Large codebase + many inline functions = noticeably longer build times.

// COST 2 — Recompilation cascade:
//   If a regular function in a .cpp changes → only THAT .cpp recompiles.
//   If an inline function in a .h changes → EVERY .cpp that includes
//   that header (directly or transitively) must recompile.
//   On large projects this cascades badly.

// ✅ USE inline in headers for: small, frequently-used utility functions
//    that NEED to be defined in headers (e.g., header-only libraries).
// ❌ DON'T put large or complex functions as inline in headers.


// ─────────────────────────────────────────────────────────────
// SECTION 8 — HEADER-ONLY LIBRARIES
// ─────────────────────────────────────────────────────────────

// A header-only library = one or more .h files that contain the FULL
// implementation — no .cpp files at all.

// Why inline makes this possible:
//   Without inline, putting function definitions in headers would cause
//   ODR violations the moment any header is included in 2+ .cpp files.
//   With inline, each .cpp can include the header without conflict.

// User's workflow with a header-only lib:
//   Step 1: #include "the_library.h"
//   Step 2: Use it.
//   → Nothing to compile separately. Nothing to link against. Done.

// This is why popular utility libs (e.g., random number generators,
// math helpers, small data structures) ship as header-only.


// ─────────────────────────────────────────────────────────────
// SECTION 9 — FUNCTIONS THAT ARE IMPLICITLY INLINE
// ─────────────────────────────────────────────────────────────

// You don't need to write `inline` for these — compiler does it automatically:

//   (a) Member functions defined INSIDE a class/struct/union body
//       class Foo {
//           int getValue() { return 42; }  // ← implicitly inline
//       };

//   (b) constexpr and consteval functions

//   (c) Function templates (when instantiated)

// For these, `inline` is redundant — don't write it.


// ─────────────────────────────────────────────────────────────
// SECTION 10 — INLINE VARIABLES (C++17)
// ─────────────────────────────────────────────────────────────

// Before C++17:
//   Putting a const variable in a header and including it in multiple
//   .cpp files was messy — had to use workarounds (const globals had
//   internal linkage by default, which caused separate copies, etc.)

// C++17 fix → inline variables:
//   Same semantics as inline functions:
//   ✅ Allowed to be defined in multiple translation units
//   ✅ All definitions must be identical
//   ✅ Linker consolidates into one
//   ✅ Compiler must see full definition at each use site

// Example — put this in a header:
// inline constexpr double pi = 3.14159;
// → Include in 10 .cpp files → 10 copies → linker deduplicates → 1 variable. ✅

// Implicitly inline variables (no `inline` keyword needed):
//   - static constexpr data members inside a class (C++17+)
//   ⚠️ Regular constexpr variables are NOT implicitly inline
//      (only constexpr FUNCTIONS are implicitly inline)


// ─────────────────────────────────────────────────────────────
// SECTION 11 — FULL MENTAL MODEL SUMMARY
// ─────────────────────────────────────────────────────────────

// `inline` has TWO distinct stories. Don't confuse them:
//
// ┌─────────────────────────────────────────────────────────┐
// │ HISTORICAL (obsolete, don't use this way)               │
// │ inline = "hint to compiler: expand this call site"      │
// │ Compiler can ignore it. Modern compilers do it better.  │
// └─────────────────────────────────────────────────────────┘
//
// ┌─────────────────────────────────────────────────────────┐
// │ MODERN (actual use today)                               │
// │ inline = "ODR exemption: this can be defined in         │
// │           multiple translation units"                   │
// │ Used for: inline functions/variables in header files    │
// │ Required: full & identical definition everywhere used   │
// └─────────────────────────────────────────────────────────┘
//
// WHY THEY'RE CONNECTED (historically):
//   To inline-expand a function in translation unit A, the compiler
//   needed the full body visible in A. But putting the body in a header
//   and including it in A and B would create two definitions → ODR error.
//   Solution: make inline functions ODR-exempt. The ODR exemption was
//   originally a consequence of the expansion feature. Today, the exemption
//   IS the feature, and expansion is the compiler's job.

// ─────────────────────────────────────────────────────────────
// BEST PRACTICES — SUMMARY
// ─────────────────────────────────────────────────────────────

// ❌ Don't use `inline` to request inline expansion — compiler ignores it.
// ✅ Use `inline` when defining a function or variable in a HEADER FILE
//    that will be included in multiple .cpp files.
// ✅ Don't manually mark implicitly-inline things (member functions,
//    constexpr functions, template instantiations).
// ⚠️ Understand: every inline function in a header is compiled once
//    per translation unit that includes it — keep them small.