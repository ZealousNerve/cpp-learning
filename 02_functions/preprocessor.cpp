#include <iostream>
 
 
// ── THE COMPILATION PIPELINE ──────────────────────────────────────────────────
//
// What actually happens when you "compile" a .cpp file:
//
//   Source (.cpp)
//       ↓
//   [PREPROCESSOR]   ← runs first, produces a "translation unit"
//       ↓
//   Translation Unit (pure C++, no directives)
//       ↓
//   [COMPILER]       ← parses and compiles C++ into object code
//       ↓
//   Object File (.obj / .o)
//       ↓
//   [LINKER]         ← combines object files into an executable
//       ↓
//   Executable (.exe / no extension)
//
// The preprocessor's output is never written to disk (usually), it's
// piped directly into the compiler. But you can see it with:
//   g++ -E yourfile.cpp   (outputs the preprocessed translation unit)
 
 
// ── WHAT THE PREPROCESSOR DOES ───────────────────────────────────────────────
//
// It scans the file TOP TO BOTTOM looking for "preprocessor directives",
// lines that start with # and end at the NEWLINE (not semicolon).
//
// Directives are NOT C++ statements:
//   ✅ #include <iostream>   ← no semicolon, it is a directive
//   ❌ #include <iostream>;  ← the semicolon is wrong (though some compilers ignore it)
//
// The preprocessor handles three main things:
//   1. #include  → file inclusion (copy-paste the contents of that file here)
//   2. #define   → macro substitution (text replacement)
//   3. #if / #ifdef / #ifndef / #endif → conditional compilation
 
 
// ── HOW #include WORKS ───────────────────────────────────────────────────────
//
// #include <iostream> does NOT "load a library at runtime."
// It is a pure text operation at compile time:
//
//   BEFORE preprocessing:
//   ┌─────────────────────────────┐
//   │ #include <iostream>         │
//   │ int main() {                │
//   │     std::cout << "Hello\n"; │
//   │ }                           │
//   └─────────────────────────────┘
//
//   AFTER preprocessing (what the compiler actually sees):
//   ┌──────────────────────────────────────────────────────────────────────────┐
//   │ [entire contents of <iostream> pasted here, thousands of lines]        │
//   │ int main() {                                                             │
//   │     std::cout << "Hello\n";                                              │
//   │ }                                                                        │
//   └──────────────────────────────────────────────────────────────────────────┘
//
// std::cout is declared inside <iostream>. After the #include substitution,
// its declaration is present in your translation unit, so the compiler accepts it.
//
// The #include is recursive, if iostream itself includes other headers,
// those are also expanded inline.
 
 
// ── ANGLE BRACKETS vs QUOTES ──────────────────────────────────────────────────
//
// #include <filename>   → search the compiler's system include paths
//                          use for: standard library, third-party installed libs
//
// #include "filename"   → search current directory first, then system paths
//                          use for: your own header files
 
 
// ── THE PREPROCESSOR IS SCOPE-UNAWARE ────────────────────────────────────────
//
// The preprocessor does not understand C++ at all. It sees only text.
// A macro defined anywhere in a file is "active" from that point to the end.
// It does not respect function boundaries, class boundaries, or namespaces.
// This is the root of why #define macros are replaced by constexpr in modern C++.
//
//   #define VALUE 42      // active from here to the end of the file
//   int foo() { ... }     // VALUE = 42 here
//   int bar() { ... }     // VALUE = 42 here too, no way to limit scope
 
 
int main()
{
    // std::cout was forward-declared by <iostream> being #included above.
    // Without the #include, the compiler would not know what std::cout is.
    std::cout << "Hello, world!\n";
 
    return 0;
}
 
 
// ── TO SEE THE PREPROCESSOR OUTPUT YOURSELF ──────────────────────────────────
//
// Run: g++ -E -std=c++17 preprocessor.cpp | head -n 50
//
// You'll see the raw iostream header contents dumped before your code.
// It's typically 20,000+ lines for <iostream> alone.
// This is why compilation takes longer when you include many headers.