/**
 * TOPIC  : Function Basics — main(), return values, status codes
 * CHAPTER: 2.1-2.2 — Introduction to functions, value-returning functions
 * SOURCE : https://learncpp.com/cpp-tutorial/introduction-to-functions/
 *
 * KEY INSIGHT: main() has two unique rules no other function has.
 *              Understanding what main() actually IS (the OS entry point)
 *              explains why these rules exist.
 */
 
#include <cstdlib>   // for EXIT_SUCCESS, EXIT_FAILURE
 
// ── RULE 1: main() must return int ─────────────────────────────────────────
// The OS receives this return value as the "exit code" of your program.
// Convention: 0 (or EXIT_SUCCESS) = ran correctly, anything else = error.
// Only 3 values are standard: 0, EXIT_SUCCESS (0), EXIT_FAILURE (1).
//
// ── RULE 2: Explicit calls to main() are forbidden ──────────────────────────
// main() is an OS entry point, not a normal function. The standard
// prohibits calling it yourself. Some C++ compilers allow it for C
// compatibility, but do not rely on this.
//
// ── MYTH: "main() always runs first" ────────────────────────────────────────
// FALSE. Global variable initializers run BEFORE main().
// If a global variable calls a function in its initializer, that function
// runs before main() ever starts. This matters in large codebases.
 
// ── CONCEPT: void functions cannot use return <value> ───────────────────────
// Value-returning functions MUST return a value (except main, which
// implicitly returns 0 if no return statement is present).
// Failure to return a value from a non-void, non-main function = UB.
 
int main()
{
    // ✅ Prefer named status codes over magic numbers
    return EXIT_SUCCESS;   // same as return 0, but more expressive
    // return EXIT_FAILURE;  // use this to signal something went wrong
}
