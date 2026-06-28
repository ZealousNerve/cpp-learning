#include <iostream>
#include <limits>
#include <cassert>
#include <cstdlib>


// ── TESTING PHILOSOPHY ──────────────────────────────────────
// Build small → test small → integrate → retest
// Never write 500 lines then test — you won't know where the bug is
// Unit test = isolate one function, prove it works, then move on

// ── 3 STAGES OF TESTING ─────────────────────────────────────

// STAGE 1: Informal — write, run, erase
bool isLowerVowel(char c) {
    switch (c) {
        case 'a': case 'e': case 'i': case 'o': case 'u': return true;
        default: return false;
    }
}
// in main() temporarily:
//   std::cout << isLowerVowel('a') << '\n';  // expect 1
//   std::cout << isLowerVowel('q') << '\n';  // expect 0
// then delete after confirming

// STAGE 2: Preserved — move tests into a function, keep for later
int testVowel() {
    if (!isLowerVowel('a')) return 1;   // returns WHICH test failed
    if ( isLowerVowel('q')) return 2;
    return 0;                            // 0 = all passed
}
// call testVowel() whenever you modify isLowerVowel
// good for regression testing (did I break something old?)

// STAGE 3: Assert-based — best style, halts program on failure
// assert(condition) — if condition is FALSE, program crashes with a message
// tells you exactly WHICH assert failed, in WHICH file, at WHICH line
// lives in <cassert>
// IMPORTANT: asserts are stripped in release builds (-DNDEBUG flag)
//            so never use assert for real error handling — only for testing
void testVowelAssert() {
    // if any of these are wrong, program stops immediately with an error
    assert(isLowerVowel('a'));
    assert(isLowerVowel('e'));
    assert(!isLowerVowel('q'));
    assert(!isLowerVowel('z'));
}
// add this guard at top of assert-test functions:
//   #ifdef NDEBUG
//       std::cerr << "Tests need asserts — don't compile with NDEBUG\n";
//       std::abort();
//   #endif

// ── CODE COVERAGE ───────────────────────────────────────────
// "How much of your code actually ran during testing?"

// STATEMENT coverage — did every line execute at least once?
// BRANCH coverage   — did every if/else/case arm execute? ← AIM FOR 100%
// LOOP coverage     — the "0, 1, 2 rule":
//   test loop with 0 iterations, 1 iteration, 2 iterations
//   if it works for 2, it works for N>2

void spam(int n) { for (int i = 0; i < n; ++i) std::cout << "Spam! "; }
// spam(0) → loop never runs
// spam(1) → runs once
// spam(2) → runs twice → if this works, spam(100) will too

// INPUT CATEGORIES — always test these for any function taking params:
// int    → negative, zero, positive, overflow edge
// float  → 0.1, -0.1, 0.7, -0.7  (these expose floating point rounding traps)
// string → empty "", all-whitespace "   ", leading/trailing spaces, normal
// ptr    → nullptr  (covered later when you do pointers)

// ── COMMON SEMANTIC ERRORS (bugs compiler WON'T catch) ──────

// 1. WRONG OPERATOR
//    if (x >= 5)  when you meant  if (x > 5)  → 5 passes when it shouldn't

// 2. INFINITE LOOP — two classic traps:
int count1 = 1;
// while (count1 <= 10) { std::cout << count1; }  ← forgot ++count1
//
// for (unsigned int i = 5; i >= 0; --i) {}  ← unsigned can't go below 0
//   when i hits 0 and decrements → wraps to 4294967295 → loop never ends
//   FIX: use signed int for countdown loops

// 3. OFF-BY-ONE
//    for (int i = 1; i < 5; ++i)   prints 1 2 3 4  (misses 5)
//    for (int i = 1; i <= 5; ++i)  prints 1 2 3 4 5  ← correct

// 4. OPERATOR PRECEDENCE
//    if (!x > y)  is actually  if ((!x) > y)  ← NOT applied to x first
//    FIX: if (!(x > y))  or just use explicit parens always

// 5. FLOAT EQUALITY — never use == on floats
//    0.1 + 0.1 + ... (10 times) != 1.0  due to rounding
//    FIX: check if  std::abs(a - b) < 0.0001  instead

// 6. INTEGER DIVISION
//    5 / 3 = 1  (not 1.666)  because both operands are int
//    FIX: static_cast<double>(x) / y

// 7. ACCIDENTAL NULL STATEMENT (the sneaky semicolon)
//    if (c == 'y');        ← semicolon here = "do nothing if true"
//        blowUpWorld();    ← this ALWAYS runs, not part of if
//    compiler won't warn — read your semicolons carefully

// 8. ASSIGNMENT INSIDE CONDITIONAL
//    if (c = 'y')   assigns 'y' to c, then evaluates c (non-zero = true)
//    always true — use  if (c == 'y')
//    modern compilers warn about this — don't ignore that warning

// 9. MISSING FUNCTION CALL OPERATOR
//    std::cout << getValue << '\n';   prints memory address (or 1)
//    std::cout << getValue() << '\n'; prints the actual return value

// ── ERROR HANDLING STRATEGIES ───────────────────────────────
// When a function detects an error, 4 options:

// 1. Handle it yourself (retry loop or ignore)
// 2. Return error to caller — via bool, sentinel value, or std::optional
// 3. std::exit(1) — use deep in call stack when you can't bubble up
// 4. throw exception — chapter 27, not now

// SENTINEL VALUE: a return value that means "something went wrong"
// works only when that value can NEVER be a valid real result
double reciprocal(double x) {
    if (x == 0.0) return 0.0;  // 0.0 is sentinel — reciprocal is never 0
    return 1.0 / x;
}
// caller checks: if (result == 0.0) → error happened

// std::cout vs std::cerr:
// cout → normal output shown to user
// cerr → errors/diagnostics — OS can redirect these separately to a log file
//        use cerr for "something went wrong" messages in non-interactive tools

// ── std::cin FAILURE MODES (4 types) ────────────────────────

// HOW cin WORKS (simplified):
// 1. strips leading whitespace from buffer
// 2. extracts characters until it hits whitespace or invalid char
// 3. on success → assigns value   on fail → assigns 0, enters "failure mode"
// in failure mode → ALL future extractions silently do nothing until clear()

// TYPE 1: Extraction succeeds but input is meaningless
//   user enters 'k' for operator → cin extracts it fine, but it's not +/-/*/
//   FIX: validate after extraction with if/switch, loop until valid

// TYPE 2: Extraction succeeds but extra junk left in buffer
//   user enters "5*7" for a number → cin grabs 5, leaves "*7\n" in buffer
//   next extraction silently grabs from that leftover — messy output
//   FIX: call ignoreLine() after every extraction

// TYPE 3: Extraction fails entirely
//   user enters 'a' for a double → cin can't convert, enters failure mode
//   all future extractions silently fail → infinite loop
//   FIX: check !cin, then call clear() FIRST, then ignoreLine()

// TYPE 4: Numeric overflow
//   user enters 40000 into int16 (max 32767) → cin fails, assigns 32767
//   same failure mode as Type 3 → same fix

// ── CORE HELPER FUNCTIONS (memorize these) ──────────────────

void ignoreLine() {
    // discards everything left in buffer up to and including '\n'
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool clearFailedExtraction() {
    if (!std::cin) {                    // did last extraction fail?
        if (std::cin.eof()) std::exit(0); // user sent EOF (Ctrl+D / Ctrl+Z) → quit
        std::cin.clear();               // MUST call clear() first — restores normal mode
        ignoreLine();                   // then flush the bad input
        return true;                    // tell caller: extraction failed
    }
    return false;
}

bool hasUnextractedInput() {
    // true = user typed extra stuff after valid input on same line
    return !std::cin.eof() && std::cin.peek() != '\n';
    // peek() looks at next char WITHOUT extracting it
}

// ── ROBUST INPUT PATTERN (the full template) ────────────────
double getDouble() {
    while (true) {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;
        if (clearFailedExtraction()) {
            std::cout << "Invalid. Try again.\n";
            continue;
        }
        ignoreLine();   // always flush trailing garbage after success too
        return x;
    }
}

char getOperator() {
    while (true) {
        std::cout << "Enter +, -, *, or /: ";
        char op{};
        std::cin >> op;
        if (!clearFailedExtraction()) ignoreLine(); // flush only if extraction succeeded
        switch (op) {
            case '+': case '-': case '*': case '/': return op;
            default: std::cout << "Invalid. Try again.\n";
        }
    }
}

// KEY RULES TO REMEMBER:
// • clear() BEFORE ignoreLine() — order matters, clear restores extraction ability
// • ignoreLine() after EVERY extraction — even successful ones
// • EOF = user is done talking — exit cleanly, don't loop
// • assert = dev/test only, stripped in release — not for production error handling