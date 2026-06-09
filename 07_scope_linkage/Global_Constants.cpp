/*
   THREE METHODS TO SHARE GLOBAL CONSTANTS:

  ──────────────────────────────────────────────────────────
  METHOD 1: Internal Variables (Header File Only)
  ──────────────────────────────────────────────────────────

  HOW IT WORKS:
  - Create constants.h with a namespace
  - Define all constants as `constexpr` inside that namespace
  - #include the header wherever you need them

  EXAMPLE:
  // constants.h
  namespace constants {
      constexpr double pi { 3.14159 };
      constexpr double gravity { 9.8 };
  }

  // main.cpp
  #include "constants.h"
  // use as: constants::pi

  ADVANTAGE:
  - Simple to set up
  - Constants are usable in compile-time expressions (array sizes, etc.)
    in EVERY file that includes the header
  - Works before C++17

  DISADVANTAGE:
  - Each .cpp that includes the header gets its OWN COPY of every constant
  - If 20 files include it → 20 copies in memory
  - Change one constant → ALL 20 files must recompile (slow for large projects)

  ──────────────────────────────────────────────────────────
  METHOD 2: External Variables (.cpp + .h forward declarations)
  ──────────────────────────────────────────────────────────

  HOW IT WORKS:
  - Define constants ONCE in constants.cpp using `extern constexpr`
  - Put `extern const` forward declarations in constants.h
  - Include the header wherever needed

  EXAMPLE:
  // constants.cpp
  namespace constants {
      extern constexpr double pi { 3.14159 };
  }

  // constants.h
  namespace constants {
      extern const double pi;  // can't forward declare as constexpr
  }

  // main.cpp
  #include "constants.h"
  // use as: constants::pi

  ADVANTAGE:
  - Only ONE copy of each variable exists in memory (defined in constants.cpp)
  - Change a value → only constants.cpp needs to recompile (fast)
  - Works before C++17

  DISADVANTAGE:
  - Forward declarations are `const`, NOT `constexpr`
  - Outside constants.cpp, compiler only sees the declaration (not the value)
  - So constants CANNOT be used in compile-time expressions
    (e.g., array sizes like `int arr[constants::size]`) in other files
  - Two files to maintain and keep in sync

  ──────────────────────────────────────────────────────────
  METHOD 3: Inline Variables in Header — BEST (C++17+)
  ──────────────────────────────────────────────────────────

  HOW IT WORKS:
  - Define constants in constants.h using `inline constexpr`
  - Include everywhere — linker deduplicates, only ONE copy exists

  EXAMPLE:
  // constants.h
  namespace constants {
      inline constexpr double pi { 3.14159 };
      inline constexpr double gravity { 9.8 };
  }

  // main.cpp
  #include "constants.h"
  // use as: constants::pi

  ADVANTAGE:
  - Only ONE copy in memory (linker deduplicates — unlike Method 1)
  - Usable in compile-time expressions in ALL files (unlike Method 2)
  - Clean — no separate .cpp file needed

  DISADVANTAGE:
  - Requires C++17 or newer
  - Change a constant → all files including the header must recompile

  ──────────────────────────────────────────────────────────
  QUICK COMPARISON TABLE:
  ──────────────────────────────────────────────────────────

  Feature                      | Method 1 | Method 2 | Method 3
  -----------------------------|----------|----------|---------
  Works before C++17           |   YES    |   YES    |   NO
  Single copy in memory        |   NO     |   YES    |   YES
  Usable in compile-time exprs |   YES    |   NO*    |   YES
  Easy to set up               |   YES    |   NO     |   YES
  Fast recompile on change     |   NO     |   YES    |   NO

  * Only usable at compile-time inside constants.cpp itself

  ──────────────────────────────────────────────────────────
  BEST PRACTICE
  ──────────────────────────────────────────────────────────
  - Default to Method 3 (inline constexpr in header) if on C++17+
  - Use Method 2 temporarily if constants change often and recompile
    times are becoming painful during active tuning
  - Method 1 is fine for small single-file programs

============================================================




*/