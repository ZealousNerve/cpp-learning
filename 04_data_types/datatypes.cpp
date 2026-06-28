//each memory address holds 1 byte of data, byte is 8 bits.

//integer vs integral datatypes:
//The standard integer types are short, int, long, long long (including their signed and unsigned variants).
//The integral types are bool, the various char types, and the standard integer types.

/*All integral types are stored in memory as integer values, but only the standard integer types will display
as an integer value when output.*/

/*
the term “integral types” only includes fundamental types. This means non-fundamental types
(such as enum and enum class) are not integral types, even when they are stored as an integer
(and in the case of enum, displayed as one too)*/

/*
Many of the types defined in newer versions of C++ (e.g. std::nullptr_t) use a _t suffix.
This suffix means “type”, and it’s a common nomenclature applied to modern types.

If you see something with a _t suffix, it’s probably a type. But many types don’t have a _t suffix,
so this isn’t consistently applied.

*/


//Void datatype:
/*
void datatypes are one which is declared but never defined, like no one knows how much memory needs to be allocated
we cannot instantiate, we can use it in function with no return type and parameter
 */

#include <iostream>
// void value; // won't work, variables can't be defined with incomplete type void

//void as parameter-deprecated

int getValue(void){// void here means no parameters
 //writing void or leaving it blank means the same
 int x{};
 std::cin >> x;
 return x;
}


/*
an object with n bits (where n is an integer) can hold 2^n (2 to the power of n, also commonly written 2^n) unique values.
Therefore, with an 8-bit byte, a byte-sized object can hold 2^8 (256) different values. An object that uses 2 bytes can
hold 2^16 (65536) different values!

The integral types char, short, int, long, and long long have a minimum size of 8, 16, 16, 32, and 64 bits respectively.
char and char8_t are exactly 1 byte (at least 8 bits).


Category        Type             Minimum Size    Typical Size
-----------------------------------------------------------------
Boolean         bool             1 byte          1 byte
Character       char             1 byte (exact)  1 byte
                wchar_t          1 byte          2 or 4 bytes
                char8_t          1 byte          1 byte
                char16_t         2 bytes         2 bytes
                char32_t         4 bytes         4 bytes
Integral        short            2 bytes         2 bytes
                int              2 bytes         4 bytes
                long             4 bytes         4 or 8 bytes
                long long        8 bytes         8 bytes
Floating point  float            4 bytes         4 bytes
                double           8 bytes         8 bytes
                long double      8 bytes         8, 12, or 16 bytes
Pointer         std::nullptr_t   4 bytes         4 or 8 bytes
 */