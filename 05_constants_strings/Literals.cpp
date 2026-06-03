/*If the default type of literal is not as desired, you can change the type of a literal by adding a suffix.
Here are some of the more common suffixes:

Numeric Literal Suffixes (C++)

u, U                     -> unsigned int
l, L                     -> long
ul, uL, Ul, UL           -> unsigned long
lu, lU, Lu, LU           -> unsigned long

ll, LL                   -> long long
ull, uLL, Ull, ULL       -> unsigned long long
llu, llU, LLu, LLU       -> unsigned long long

z, Z                     -> signed std::size_t (C++23)
uz, uZ, Uz, UZ           -> std::size_t (C++23)
zu, zU, Zu, ZU           -> std::size_t (C++23)

f, F                     -> float
l, L                     -> long double

s                        -> std::string
sv                       -> std::string_view


s and sv must be lower case.
Two consecutive l or L characters must have the same casing (lL and Ll are not accepted).
*/

#include <iostream>

int main(){
    std::cout << 5 << '\n';  // 5 (no suffix) is type int (by default)
    std::cout << 5L << '\n'; // 5L is type long
    std::cout << 5u << '\n'; // 5u is type unsigned int
    return 0;
}


//STRING LITERALS:

/*
There are two non-obvious things worth knowing about C-style string literals.

1. All C-style string literals have an implicit null terminator ('\0')
2. C-style string literals are const objects that are created at the start of the program and are guaranteed to
   exist for the entirety of the program.


*/

// A magic number is a literal (usually a number) that either has an unclear meaning or may need to be changed later.
//Avoid magic numbers in your code (use constexpr variables instead



//OPTIONAL PART:

//Because long literals can be hard to read, C++14 also adds the ability to use a quotation mark (‘) as a digit separator.
long value { 2'132'673'462 }; // much easier to read than 2132673462
int bin { 0b1011'0010 };  // assign binary 1011 0010 to the variable


int main(){ //output in different literals
    int x { 12 };
    std::cout << x << '\n'; // decimal (by default)
    std::cout << std::hex << x << '\n'; // hexadecimal
    std::cout << x << '\n'; // now hexadecimal
    std::cout << std::oct << x << '\n'; // octal
    std::cout << std::dec << x << '\n'; // return to decimal
    std::cout << x << '\n'; // decimal
    return 0;
}


//OUTPUT IN BINARY
#include <bitset> // for std::bitset
#include <iostream> //used previously

int main()
{
    // std::bitset<8> means we want to store 8 bits
    std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
    std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

    std::cout << bin1 << '\n' << bin2 << '\n';
    std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

    return 0;
}


/*
In the above code, this line:

std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

creates a temporary (unnamed) std::bitset object with 4 bits, initializes it with binary literal 0b1010,
prints the value in binary, and then discards the temporary object.

 */


//In C++20 and C++23, we have better options for printing binary via the new Format Library (C++20) and Print Library (C++23):

#include <format> // C++20
#include <iostream>
#include <print> // C++23
int main(){
    std::cout << std::format("{:b}\n", 0b1010);  // C++20, {:b} formats the argument as binary digits
    std::cout << std::format("{:#b}\n", 0b1010); // C++20, {:#b} formats the argument as 0b-prefixed binary digits

    std::println("{:b} {:#b}", 0b1010, 0b1010);  // C++23, format/print two arguments (same as above) and a newline
    return 0;
}


