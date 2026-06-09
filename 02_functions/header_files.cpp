#include <iostream>
 
 
// ── THE PROBLEM HEADER FILES SOLVE ───────────────────────────────────────────
//
// C++ compiles each .cpp file independently. This means:
//   - math.cpp defines add()
//   - main.cpp calls add()
//   - The compiler processing main.cpp has NO idea add() exists
//   - Without a declaration, it refuses to compile main.cpp
//
// You could copy the declaration into every .cpp file that needs it,
// but that scales terribly with 100+ files. And if the signature changes,
// you'd update it in 100 places.
//
// ✅ Solution: put the declaration ONCE in a header file.
//              Every .cpp file that needs it #includes that header.
//              One source of truth, automatically distributed.
 
 
// ── WHAT A HEADER FILE CONTAINS ──────────────────────────────────────────────
//
// A header file typically has two parts:
//
//   PART 1: Header guard (prevents multiple inclusion)
//             #ifndef MY_HEADER_H
//             #define MY_HEADER_H
//             ...
//             #endif
//             (see header_guards.cpp)
//
//   PART 2: Declarations only, no definitions
//             int add(int x, int y);          ← declaration ✅
//             int add(int x, int y) { ... }   ← definition ❌ (in header = ODR violation risk)
//
// Putting a DEFINITION in a header causes "multiple definition" linker errors
// when two .cpp files both include that header. Each inclusion copy-pastes the
// definition, giving the linker two definitions of the same function.
 
 
// ── HOW #include WORKS WITH HEADERS ──────────────────────────────────────────
//
// #include "add.h" is a preprocessor directive. It literally copies the
// entire contents of add.h and pastes it at the point of the #include.
//
// After preprocessing, main.cpp looks as if you wrote the declaration yourself:
//
//   BEFORE:                          AFTER:
//   #include "add.h"                 int add(int, int);   ← pasted from add.h
//   int main() {                     int main() {
//       add(3, 4);                       add(3, 4);
//   }                                }
//
// This is why the compiler can validate the call to add(), its declaration
// is now present in the translation unit.
 
 
// ── ANGLE BRACKETS vs QUOTES ──────────────────────────────────────────────────
//
// #include <iostream>    → angle brackets: search compiler's system include paths
//                          use for: C++ standard library, OS headers, installed libs
//
// #include "myHeader.h"  → quotes: search current directory FIRST, then system paths
//                          use for: your own project's header files
//
// Using angle brackets for your own headers works on most setups but is
// technically wrong, quotes convey the intent ("local file") clearly.
 
 
// ── STANDARD LIBRARY HEADERS: NO .h EXTENSION ────────────────────────────────
//
// The C++ standard library headers have NO file extension:
//   ✅ #include <iostream>    (C++ standard)
//   ❌ #include <iostream.h>  (old C++, obsolete, avoid)
//
// C standard library headers accessed from C++ use the c prefix, no .h:
//   ✅ #include <cstdlib>     (C++ way to include C's stdlib.h)
//   ✅ #include <cmath>       (C++ way to include C's math.h)
//   ❌ #include <stdlib.h>    (works but is the C way, avoid in C++ code)
//
// Your OWN header files should use the .h extension: mymath.h, player.h, etc.
 
 
// ── WHAT NOT TO DO IN HEADERS ─────────────────────────────────────────────────
//
// ❌ Function definitions in headers (ODR violation risk)
//     int add(int x, int y) { return x + y; }   // NEVER in a header
//
// ❌ Variable definitions in headers (ODR violation risk)
//     int globalCounter = 0;   // NEVER in a header
//
// ❌ #include-ing .cpp files
//     #include "math.cpp"   // illegal by convention, causes redefinition errors
//
// ❌ Using relative paths in #include directives
//     #include "../utils/helper.h"   // fragile, breaks if directory structure changes
//     // Instead: add the include directory to your compiler's -I flag
//
// ✅ What belongs in headers:
//     Function declarations (prototypes)
//     Class declarations
//     Type definitions (typedefs, using aliases)
//     constexpr / inline variables
//     Template definitions (special case, must be in headers for linkage reasons)
//     Other #includes that this header itself depends on
 
 
// ── INCLUDING HEADERS THAT INCLUDE OTHER HEADERS ─────────────────────────────
//
// It is common for headers to #include other headers they depend on.
// For example, a Vector3D.h might #include <cmath> because it uses sqrt().
// This is fine, the preprocessor handles recursive inclusion.
// Header guards (next file) prevent the same header from being included twice.
 
 
int main()
{
    // std::cout is declared in <iostream>.
    // #include <iostream> above copies that declaration into this file.
    // Without it: "error: 'cout' is not a member of 'std'"
    std::cout << "Header files demonstrated\n";
 
    return 0;
}
 