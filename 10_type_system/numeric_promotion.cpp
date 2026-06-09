// ── WHY PROMOTIONS EXIST ────────────────────────────────────
// 32-bit CPU works the fastest on 32-bit data.
// Operating on 8-bit (char) or 16-bit (short) can be SLOWER.
// So C++ automatically "promotes" narrow types to int/double
// before doing work — this is numeric promotion.
//
// Also solves redundancy: you write ONE printInt(int x),
// and char, short, bool all get promoted to int to match it.
// Without promotion, you'd need a separate overload for each type.


// ── FLOATING POINT PROMOTION ────────────────────────────────
// Only one rule: float → double
// That's it. float is the only type that gets promoted this way.

#include <iostream>

void printDouble(double d) { std::cout << d << '\n'; }

int main()
{
    printDouble(5.0);   // double → no conversion needed
    printDouble(4.0f);  // float → promoted to double ✅

    return 0;
}


// ── INTEGRAL PROMOTIONS ─────────────────────────────────────
// Assuming 8-bit byte, 4-byte int (standard today):
//
//  bool            → int   (false=0, true=1)
//  char            → int   (signed or unsigned depending on platform)
//  signed char     → int
//  unsigned char   → int
//  signed short    → int
//  unsigned short  → int   (or unsigned int if int can't hold full range)
//
// Bottom line: bool, char, and short → int. That's what matters.

void printInt(int x) { std::cout << x << '\n'; }

int main()
{
    printInt(2);       // int → no conversion

    short s { 3 };
    printInt(s);       // short → promoted to int ✅
    printInt('a');     // char  → promoted to int (prints 97) ✅
    printInt(true);    // bool  → promoted to int (prints 1)  ✅

    return 0;
}


// ── KEY DISTINCTION — PROMOTION vs CONVERSION ───────────────
// NOT all widening is promotion. This trips people up:

//The number of bits a data type uses is called its width. A wider data type is one that uses more bits, and a narrower
//data type is one that uses fewer bits.
//
//  char  → short   ❌ NOT a promotion (numeric conversion instead)
//  int   → long    ❌ NOT a promotion (numeric conversion instead)
//
// Promotion = specific narrow-to-efficient-width upgrades only.
// Conversion = everything else (covered in 10.3).
//
// Why does this matter? In function overload resolution (ch.11),
// compiler PREFERS promotions over conversions when picking
// which overloaded function to call. Know the difference exists.


// ── SIGNEDNESS NOTE ─────────────────────────────────────────
// Promotion is value-preserving but NOT necessarily sign-preserving.
// unsigned char can get promoted to signed int — value is safe,
// but the sign of the type changed. Rarely causes bugs, just be aware.