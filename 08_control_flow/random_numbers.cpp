/*
=============================================================
  RANDOM NUMBER GENERATION IN C++ — Chapters 8.13 & 8.14
=============================================================

CORE CONCEPT:
  Computers can't generate truly random numbers.
  They simulate randomness using algorithms — called PRNGs.
  (Pseudo-Random Number Generator)

HOW A PRNG WORKS:
  1. It holds an internal "state" (some value)
  2. Each call: it modifies the state using math ops
  3. Returns a number derived from that new state
  → Deterministic: same starting state = same output sequence

KEY TERM — SEED:
  The initial value used to set the PRNG's state.
  Same seed → same sequence of numbers every time.
  Different seed → different sequence.
*/


// ─────────────────────────────────────────
// MERSENNE TWISTER — the one you actually use
// ─────────────────────────────────────────
/*
  std::mt19937     → 32-bit Mersenne Twister  ✅ use this
  std::mt19937_64  → 64-bit version

  Why MT? As of C++20, it's the only PRNG in the standard
  library with both decent performance AND quality.

  ⚠️  Downside: results can be predicted after seeing 624
  generated numbers → not suitable for cryptography.

  Header needed: #include <random>
*/

#include <iostream>
#include <random>

int main()
{
    std::mt19937 mt{}; // value-initialized = seeded with 0 (bad, but shows basic usage)

    for (int count{ 1 }; count <= 10; ++count)
        std::cout << mt() << '\t'; // mt() generates next random number

    return 0;
}


// ─────────────────────────────────────────
// LIMITING RANGE — uniform_int_distribution
// ─────────────────────────────────────────
/*
  mt19937 alone generates numbers in 0 to 4,294,967,295.
  To get numbers in a range (e.g., 1 to 6), use a distribution.

  std::uniform_int_distribution → equal probability for all values in range
*/

#include <iostream>
#include <random>

int main()
{
    std::mt19937 mt{ std::random_device{}() }; // properly seeded (see below)

    std::uniform_int_distribution die6{ 1, 6 }; // range [1, 6]
    // C++14 and below: std::uniform_int_distribution<> die6{ 1, 6 };

    for (int count{ 1 }; count <= 10; ++count)
        std::cout << die6(mt) << '\t'; // pass mt into the distribution

    return 0;
}


// ─────────────────────────────────────────
// THE SEEDING PROBLEM
// ─────────────────────────────────────────
/*
  If you value-initialize mt19937 like mt19937 mt{},
  it uses the same seed every run → same numbers every run.

  TWO SOLUTIONS:

  1. Seed with system clock (okay, not great):
     - Different each run ✅
     - But if run twice quickly, seeds are too similar ❌
*/

#include <chrono>
std::mt19937 mt{ static_cast<std::mt19937::result_type>(
    std::chrono::steady_clock::now().time_since_epoch().count()
)};
// std::chrono::high_resolution_clock is also popular, but user can modify it
// steady_clock can't be changed by user → more reliable

/*
  2. Seed with std::random_device (BEST PRACTICE ✅):
     - Asks the OS for a pseudo-random number
     - Different each run on modern compilers (GCC, Clang, MSVC)
     - ⚠️  On some old systems (MinGW bug, fixed in GCC 9.2), it was broken
*/

std::mt19937 mt2{ std::random_device{}() };
// std::random_device{} → creates temporary object
// {}()                 → calls operator() → gets one random value as seed


// ─────────────────────────────────────────
// UNDERSEEDING PROBLEM & std::seed_seq FIX
// ─────────────────────────────────────────
/*
  mt19937 has 624 integers of internal state.
  Seeding it with just ONE value (from random_device) = underseeded.
  → It fills the other 623 slots with "guessed" values.
  → Result: seeding with 42 will NEVER produce 42 as first output.

  FIX: Use std::seed_seq with multiple random_device values.
  More seed bits = better quality randomness.
  8 values from random_device is a good minimum.
*/

#include <iostream>
#include <random>

int main()
{
    std::random_device rd{};
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // 8 random seeds
    std::mt19937 mt{ ss }; // initialize MT with the seed_seq

    std::uniform_int_distribution die6{ 1, 6 };

    for (int count{ 1 }; count <= 40; ++count)
    {
        std::cout << die6(mt) << '\t';
        if (count % 10 == 0) std::cout << '\n';
    }

    return 0;
}


// ─────────────────────────────────────────
// COMMON MISTAKES
// ─────────────────────────────────────────

// ❌ BAD: creating + seeding PRNG inside a function that's called repeatedly
int getCard_BAD()
{
    std::mt19937 mt{ std::random_device{}() }; // re-seeded every call → bad quality + slow
    std::uniform_int_distribution card{ 1, 52 };
    return card(mt);
}

// ✅ GOOD: create PRNG once, reuse it
int getCard_GOOD()
{
    static std::mt19937 mt{ std::random_device{}() }; // initialized only once
    std::uniform_int_distribution card{ 1, 52 };
    return card(mt);
}

/*
  RULE: Only seed a PRNG once. Never reseed unless you have a specific reason.
  Reseeding mid-use = less random results.
*/


// ─────────────────────────────────────────
// DEBUGGING TIP
// ─────────────────────────────────────────
/*
  Programs using random numbers behave differently each run → hard to debug.

  FIX: Temporarily seed with a fixed value while debugging.
  Once bug is reproduced and fixed, switch back to random_device.
*/

std::mt19937 mt_debug{ 5 }; // fixed seed → same output every debug run


// ─────────────────────────────────────────
// QUICK REFERENCE — WHICH PRNG TO USE?
// ─────────────────────────────────────────
/*
  minstd_rand       → NO  (awful quality)
  mt19937 / _64     → YES (decent, good for most use cases)
  ranlux24/48       → NO  (awful performance)
  knuth_b           → NO  (awful everything)
  default_random_engine → NO (implementation-defined, unpredictable)
  rand()            → NO  (legacy C, awful)

  For crypto/non-predictability? → Use a 3rd party lib (Xoshiro, Chacha family)
*/