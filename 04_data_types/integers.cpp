//By default, integers in C++ are signed, which means the number’s sign is stored as part of the value.
//Therefore, a signed integer can hold both positive and negative numbers (and 0).

//Here is the preferred way to define the four types of signed integers:

short s;      // prefer "short" instead of "short int"
int i;
long l;       // prefer "long" instead of "long int"
long long ll; // prefer "long long" instead of "long long int"

//The integer types can also take an optional signed keyword, which by convention is typically placed before the type name:
//Prefer the shorthand types that do not use the int suffix or signed prefix.

//The range of an integer variable is determined by two factors: its size (in bits), and whether it is signed or not.

/*
Size/Type          Range
8-bit signed	-128 to 127
16-bit signed	-32,768 to 32,767
32-bit signed	-2,147,483,648 to 2,147,483,647
64-bit signed	-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807

an n-bit signed variable has a range of -(2n-1) to (2n-1)-1.
The above ranges assume “two’s complement” binary representation.

In prior standards, sign-magnitude and ones complement representations were permitted for historical reasons.
Such representations produce values in the range -(2n-1-1) to +(2n-1-1).

The number 140 requires 9 bits to represent (8 magnitude bits and 1 sign bit)
 */


/*
f an arithmetic operation (such as addition or multiplication) attempts to create a value outside the range
that can be represented, this is called integer overflow (or arithmetic overflow). For signed integers,
integer overflow will result in undefined behavior.
 */

#include <iostream>
int main(){
 // assume 4 byte integers
 int x { 2'147'483'647 }; // the maximum value of a 4-byte signed integer
 std::cout << x << '\n';

 x = x + 1; // integer overflow, undefined behavior
 std::cout << x << '\n'; //prints (-2147483647)
 return 0;
}


//UNSIGNED INTEGER

//To define an unsigned integer, we use the unsigned keyword. By convention, this is placed before the type:
/*
Size/Type	      Range
8 bit unsigned	 0 to 255
16 bit unsigned	 0 to 65,535
32 bit unsigned	 0 to 4,294,967,295
64 bit unsigned	 0 to 18,446,744,073,709,551,615

An n-bit unsigned variable has a range of 0 to (2n)-1.

If an unsigned value is out of range, it is divided by one greater than the largest number of the type, and only the remainder kept.

The number 280 is too big to fit in our 1-byte range of 0 to 255. 1 greater than the largest number of the type is 256.
Therefore, we divide 280 by 256, getting 1 remainder 24. The remainder of 24 is what is stored.

It’s possible to wrap around the other direction as well. 0 is representable in a 2-byte unsigned integer,
so that’s fine. -1 is not representable, so it wraps around to the top of the range, producing the value 65535.
-2 wraps around to 65534. And so forth.
 */


//FIXED INTEGERS
//an int has a minimum size of 16-bits, but it’s typically 32-bits on modern architectures.

/*
if  we assume int to be 32 then it will overflow on older architecture based computers, if we assume 16 bits thinking
that it will work on both but as we know every time we will create a int on modern architecture then half of the memory
will be still unused everytime

size of int is not fixed because in early days of C, the size of int were decided by the compiler, based on the architecture

to fix such issue C++ has a fixed set of integers, which performs with fixed size on every architecture


Type            Size        Range
std::int8_t     1 byte      -128 to 127 (signed char)
std::uint8_t    1 byte      0 to 255 (unsigned char)

std::int16_t    2 bytes     -32,768 to 32,767
std::uint16_t   2 bytes     0 to 65,535

std::int32_t    4 bytes     -2,147,483,648 to 2,147,483,647
std::uint32_t   4 bytes     0 to 4,294,967,295

std::int64_t    8 bytes     -9,223,372,036,854,775,808
                            to 9,223,372,036,854,775,807

std::uint64_t   8 bytes     0 to 18,446,744,073,709,551,615

on most modern systems, the 8-bit fixed-width integral types will behave like char types.
 */

#include <cstdint> // for fixed-width integers
int main(){
 std::int32_t x { 32767 }; // x is always a 32-bit integer
 x = x + 1;                // so 32768 will always fit
 std::cout << x << '\n';
 return 0;
}

/*
std::int8_t x { 65 };   // initialize 8-bit integral type with value 65
std::cout << x << '\n'; // You're probably expecting this to print 65 (most likely it will not)



The fixed-width integers actually don’t define new types -- they are just aliases for existing integral types with the
desired size. For each fixed-width type, the implementation (the compiler and standard library) gets to determine which
existing type is aliased. As an example, on a platform where int is 32-bits, std::int32_t will be an alias for int.
On a system where int is 16-bits (and long is 32-bits), std::int32_t will be an alias for long instead.

In most cases, std::int8_t is an alias for signed char because it is the only available 8-bit signed integral type

However, in rare cases, if a platform has an implementation-specific 8-bit signed integral type, the implementation
may decide to make std::int8_t an alias for that type instead. In that case, std::int8_t will behave like that type,

using a fixed integer slow down our code execution, and there is not a necessity that these fixed type are present on
every architecture, it will be for sure present on the modern one but very slow, and to solve this there are two other
types of integers which are guaranteed to exist i.e. fast and least integral types
 */

/*
The fast types (std::int_fast#_t and std::uint_fast#_t) provide the fastest signed/unsigned integer type with a width
of at least # bits (where # = 8, 16, 32, or 64). For example, std::int_fast32_t will give you the fastest signed integer
type that’s at least 32-bits. By fastest, we mean the integral type that can be processed most quickly by the CPU.

The least types (std::int_least#_t and std::uint_least#_t) provide the smallest signed/unsigned integer type with a
width of at least # bits (where # = 8, 16, 32, or 64). For example, std::uint_least32_t will give you the smallest
unsigned integer type that’s at least 32-bits.
 */

//the includes given below are feel commented because they are defined above, and we cannot do twice

#include <cstdint> // for fast and least types
#include <iostream>

int main(){
 std::cout << "least 8:  " << sizeof(std::int_least8_t)  * 8 << " bits\n";
 std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
 std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
 std::cout << '\n';
 std::cout << "fast 8:  "  << sizeof(std::int_fast8_t)   * 8 << " bits\n";
 std::cout << "fast 16: "  << sizeof(std::int_fast16_t)  * 8 << " bits\n";
 std::cout << "fast 32: "  << sizeof(std::int_fast32_t)  * 8 << " bits\n";
 return 0;
}

/*
std::int_least16_t is 16-bits, whereas std::int_fast16_t is actually 32-bits.
This is because on the author’s machine, 32-bit integers are faster to process than 16-bit integers.

let’s assume we’re on an architecture that has only 16-bit and 64-bit integral types. std::int32_t would not exist,
whereas std::least_int32_t (and std::fast_int32_t) would be 64 bits.

these fast and least integers have their own downsides. First, not many programmers actually use them, and a lack of
familiarity can lead to errors. Then the fast types can also lead to memory wastage, as their actual size may be
significantly larger than indicated by their name.
*/