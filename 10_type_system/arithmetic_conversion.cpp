/*In this case, operator+ is being given one operand of type int and another of type double. Should the result of the
operator be returned as an int, a double, or possibly something else altogether?

In C++, certain operators require that their operands be of the same type. If one of these operators is invoked with
operands of different types, one or both of the operands will be implicitly converted to matching types using a set
of rules called the usual arithmetic conversions. The matching type produced as a result of the usual arithmetic
conversion rules is called the common type of the operands.



>>> The following operators require their operands to be of the same type:

*The binary arithmetic operators: +, -, *, /, %
*The binary relational operators: <, >, <=, >=, ==, !=
*The binary bitwise arithmetic operators: &, ^, |
*The conditional operator ?: (excluding the condition, which is expected to be of type bool)

------------------------------------------------------------------------------------------------------------------------

//ARITHMETIC CONVERSION RULE:

>>> The usual arithmetic conversion rules are somewhat complex, so we’ll simplify a bit. The compiler has a ranked list
of types that looks something like this:

1. long double (highest rank)
2. double
3. float
4. long long
5. long
6. int (lowest rank)

The following rules are applied to find a matching type:

Step 1:
    If one operand is an integral type and the other a floating point type, the integral operand is converted to the
    type of the floating point operand (no integral promotion takes place).
    Otherwise, any integral operands are numerically promoted.


Step 2:
    After promotion, if one operand is signed and the other unsigned, special rules apply

    * If the rank of the unsigned operand is greater than or equal to the rank of the signed operand,
      the signed operand is converted to the type of the unsigned operand.

    * If the type of the signed operand can represent all the values of the type of the unsigned operand,
      the type of the unsigned operand is converted to the type of the signed operand.

    * Otherwise both operands are converted to the corresponding unsigned type of the signed operand.

    Otherwise, the operand with lower rank is converted to the type of the operand with higher rank.

=====================================================================================================================
std::common_type_t<int, double> returns the common type of int and double, and std::common_type_t<unsigned int, long>
returns the common type of unsigned int and long.
=====================================================================================================================
 */

//Examples

#include <iostream>
#include <typeinfo>

int main()
{
    // --- Numeric promotion: short -> int ---
    short a{ 4 };
    short b{ 5 };
    // Neither short is on the priority list, so both get promoted to int first
    std::cout << "short + short -> " << typeid(a + b).name() << " : " << a + b << '\n';

    // --- Numeric conversion: int -> double (double has higher priority) ---
    int   i{ 2 };
    double d{ 3.5 };
    // int is converted to double 2.0, then added to 3.5
    std::cout << "int   + double -> " << typeid(i + d).name() << " : " << i + d << '\n';

    // --- The signed/unsigned trap #1: subtraction wraps around ---
    unsigned int u{ 5u };
    // int 10 is converted to unsigned int first (unsigned has priority over signed)
    // then: 5u - 10u => wraps around because unsigned can't hold -5
    // result = 2^32 - 5 = 4294967291 on a 32-bit unsigned int
    std::cout << "\n5u - 10  -> " << typeid(5u - 10).name() << " : " << 5u - 10 << '\n';
    std::cout << "(expected -5, got a huge positive number — unsigned wraparound)\n";

    // --- The signed/unsigned trap #2: comparison gives wrong result ---
    // -3 is converted to unsigned int before comparison
    // -3 as unsigned = 4294967293 which is WAY bigger than 5u
    // so (-3 < 5u) evaluates to FALSE — completely counterintuitive
    std::cout << "\n(-3 < 5u) -> " << std::boolalpha << (-3 < 5u) << '\n';
    std::cout << "(expected true, got false — -3 became a huge unsigned number)\n";

    // --- Safe version: cast explicitly to avoid the trap ---
    std::cout << "\n(-3 < (int)5u) -> " << (-3 < (int)5u) << '\n';
    std::cout << "(now it correctly returns true)\n";

    return 0;
}



/*
//OUTPUT

    short + short -> int : 9
    int   + double -> double : 5.5

    5u - 10  -> unsigned int : 4294967291
    (expected -5, got a huge positive number — unsigned wraparound)

    (-3 < 5u) -> false
    (expected true, got false — -3 became a huge unsigned number)

    (-3 < (int)5u) -> true
    (now it correctly returns true)

*/