#include <iostream>


/* ──────────────────────────────────────────────────────────
 *    USING DECLARATIONS & USING DIRECTIVES
 * ────────────────────────────────────────────────────────── */


// ── TYPE 1: Using-Declaration ──────────────────────────────
//
// Brings ONE specific name from a namespace into scope.
// Syntax:  using std::cout;
// After this, you write cout instead of std::cout.
// Scope: limited to the block it appears in — safe.

void example_using_declaration()
{
    using std::cout;   // only cout is brought in — cin, endl etc. are NOT
    using std::cin;    // each name needs its own using-declaration

    int x{};
    cout << "Enter a number: ";
    cin >> x;          // works — we explicitly declared both cout and cin
    cout << x << '\n';

} // <-- both using-declarations expire here; no effect outside this block


// ── TYPE 2: Using-Directive ────────────────────────────────
//
// Brings ALL names from a namespace into scope at once.
// Syntax:  using namespace std;
// Seen in bad textbooks. Avoid in real code — see problems below.

void example_using_directive_BAD()
{
    using namespace std;   // ALL of std dumped into this scope
    cout << "Hello\n";     // works, but risky — see why below
}


/* ──────────────────────────────────────────────────────────
 *  WHY "using namespace std;" IS DANGEROUS — 3 PROBLEMS
 * ────────────────────────────────────────────────────────── */


// PROBLEM 1: Immediate naming collision
//
// Your own function and std have the same name → compiler can't decide → error.

namespace MyLib { void cout() {} }   // a function also named cout

void problem1()
{
    using namespace std;
    using namespace MyLib;
    // cout << "hi";   // ERROR: ambiguous — is this std::cout or MyLib::cout?
}


// PROBLEM 2: Silent break when a library updates
//
// You wrote print() yourself. Later, Foo adds its own print(int).
// With "using namespace Foo", your call to print() may silently
// route to Foo::print() instead of yours — behavior changes invisibly.

namespace Foo_v1 { void print(int x) { /* library's new version */ } }

void myPrint() {}   // your original function

void problem2()
{
    using namespace Foo_v1;
    // print() — used to call myPrint(), now ambiguous after Foo added print(int)
    // Your code didn't change. The library did. But YOUR program broke.
}


// PROBLEM 3: Argument-type hijack (overload resolution surprise)
//
// Your function: get(long)  → returns 1
// Library adds:  get(int)   → returns 2
// Call: get(0)  — 0 is an int literal, so compiler now prefers get(int)
// from the library over your get(long). Silent wrong result.

namespace Lib { int get(int)  { return 2; } }   // library adds this later

int get(long) { return 1; }   // your original function

void problem3()
{
    using namespace Lib;
    int result = get(0);   // 0 is int → compiler picks Lib::get(int) → returns 2
                           // you expected 1 — nothing in YOUR code changed
    (void)result;
}


/* ──────────────────────────────────────────────────────────
 *  SCOPE RULES FOR USING-STATEMENTS
 * ────────────────────────────────────────────────────────── */

// Inside a function block  → expires at closing brace (safe)
// At global scope          → affects the ENTIRE rest of the file (risky)
// Inside a header file     → infects EVERY file that #includes it (never do this)

// BAD — global scope using-directive in a .cpp file:
// using namespace std;   // affects everything below in this file
// #include "MyHeader.h"  // now MyHeader.h is also polluted

// ALSO BAD — using-statement placed BEFORE an #include:
// using Foo::print;      // compiler hasn't seen Foo's overloads yet
// #include "FooInt.h"    // too late — wrong overload may already be chosen


// ── Correct placement ──────────────────────────────────────
//
// In a .cpp file, AFTER all #includes, inside a function block.

// #include "something.h"   ← all includes first
//
// void myFunc()
// {
//     using std::cout;     ← then using-declaration, inside the block
//     cout << "Safe\n";
// }


// ── Cancelling a using-statement — NOT possible ────────────
//
// Once declared, it cannot be undone within its scope.
// Workaround: use separate blocks to contain each directive.

void example_scoped_namespaces()
{
    {
        using namespace Foo_v1;   // Foo is available here
        // ... Foo stuff ...
    }                             // Foo expires here

    {
        // using namespace Goo;   // Goo available here only
        // ... Goo stuff ...
    }                             // Goo expires here

    // Alternatively: just use std:: explicitly everywhere — zero ambiguity
    std::cout << "Explicit is always safe\n";
}


/* ──────────────────────────────────────────────────────────
 *  BEST PRACTICE SUMMARY — 7.13
 * ──────────────────────────────────────────────────────────
 *
 *  PREFER  : explicit std::cout, std::cin — always clear, zero risk
 *  OKAY    : using-declarations in .cpp files, after all #includes, inside blocks
 *  AVOID   : using-directives (using namespace std / using namespace X)
 *  NEVER   : using-statements in header files
 *  NEVER   : using-statements placed before an #include
 *  EXCEPTION: using namespace std::literals is fine (enables s/sv literal suffixes)
 * ────────────────────────────────────────────────────────── */


/* ══════════════════════════════════════════════════════════
 *  CHAPTER 7.14 — UNNAMED & INLINE NAMESPACES
 * ══════════════════════════════════════════════════════════ */


// ── Unnamed (Anonymous) Namespaces ────────────────────────
//
// A namespace with no name: namespace { ... }
// All contents are automatically part of the parent namespace,
// so you call them without any prefix.
// Everything inside also gets INTERNAL LINKAGE automatically —
// meaning it is invisible outside this .cpp file.

namespace   // unnamed — no identifier after the keyword
{
    void doSomethingPrivate()
    {
        std::cout << "Only visible in this file\n";
    }

    int helperValue{ 42 };   // internal linkage — other .cpp files cannot see this
}

// Equivalent to writing static in front of every declaration:
// static void doSomethingPrivate() { ... }   // same effect for functions
// NOTE: static does NOT work for type definitions — unnamed namespace does

void example_unnamed_namespace()
{
    doSomethingPrivate();   // no prefix needed — it's part of the enclosing scope
    std::cout << helperValue << '\n';   // also accessible without prefix
}


// ── Inline Namespaces ─────────────────────────────────────
//
// Used for VERSIONING a library.
// The inline version is the DEFAULT — callable without any prefix.
// Non-inline versions require an explicit prefix to access.

inline namespace V1   // inline = this version is the default
{
    void doSomething() { std::cout << "V1\n"; }
}

namespace V2          // not inline = must use V2:: prefix to call
{
    void doSomething() { std::cout << "V2\n"; }
}

void example_inline_namespace_v1_default()
{
    doSomething();       // calls V1::doSomething() — V1 is inline (default)
    V2::doSomething();   // explicit prefix required for non-default version
}


// ── Switching the default to V2 ───────────────────────────
//
// When you release a new version and want it to be the default,
// move the inline keyword to V2. Existing callers who used V1::
// explicitly are unaffected.

namespace V1_old          // V1 is no longer default — callers must use V1_old::
{
    void doSomethingOld() { std::cout << "V1 old\n"; }
}

inline namespace V2_new   // V2 is now the default
{
    void doSomethingOld() { std::cout << "V2 new\n"; }
}

void example_inline_namespace_v2_default()
{
    doSomethingOld();            // now calls V2_new — it's the new inline default
    V1_old::doSomethingOld();    // old code that needs V1 must be explicit
}


// ── Combining Inline + Unnamed ────────────────────────────
//
// Best pattern: nest an unnamed namespace inside an inline namespace.
// Result: the content is version-defaulted AND file-private.

inline namespace V3
{
    namespace          // unnamed inside inline — gives internal linkage
    {
        void doSomethingInternal()
        {
            std::cout << "V3, file-private\n";
        }
    }
}

void example_combined()
{
    doSomethingInternal();       // works — V3 is inline (default)
    V3::doSomethingInternal();   // also works — explicit prefix still valid
    // Other .cpp files cannot see doSomethingInternal() at all
}


/* ──────────────────────────────────────────────────────────
 *  BEST PRACTICE SUMMARY — 7.14
 * ──────────────────────────────────────────────────────────
 *
 *  UNNAMED NAMESPACE  : use when content must stay private to one .cpp file
 *                       (cleaner than writing static on every declaration;
 *                        also works for types, which static cannot handle)
 *  INLINE NAMESPACE   : use for library versioning — inline version = default,
 *                       older versions still reachable via explicit prefix
 *  HEADER FILES       : avoid unnamed namespaces in headers
 * ────────────────────────────────────────────────────────── */


int main()
{
    example_using_declaration();
    example_using_directive_BAD();
    problem1();
    problem2();
    problem3();
    example_scoped_namespaces();
    example_unnamed_namespace();
    example_inline_namespace_v1_default();
    example_inline_namespace_v2_default();
    example_combined();

    return 0;
}