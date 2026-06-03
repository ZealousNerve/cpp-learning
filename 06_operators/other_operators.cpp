#include <cmath>
#include <iostream>
int main(){


    //to do exponent in c++ we use pow function and by including cmath
    double x{ std::pow(3.0, 4.0) }; // 3 to the 4th power


//COMMA operator

    /*The comma operator (,) allows you to evaluate multiple expressions wherever a single expression is allowed.
    The comma operator evaluates the left operand, then the right operand, and then returns the result of the right operand.*/

    int x{ 1 };
    int y{ 2 };
    std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand

    /*First the left operand of the comma operator is evaluated, which increments x from 1 to 2. Next,
    the right operand is evaluated, which increments y from 2 to 3. The comma operator returns the
    result of the right operand (3), which is subsequently printed to the console.

    Note that comma has the lowest precedence of all the operators, even lower than assignment.
    Because of this, the following two lines of code do different things*/

    int a, b, z;
    z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.
    z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.
    std::cout << z << '\n';


//CONDITIONAL operator

    //Conditional	?:	c ? x : y	If conditional c is true then evaluate x, otherwise evaluate y
    //Parenthesize the entire conditional operation (including operands) when used in a compound expression.

    /*
    1. The type of the second and third operand must match.
    2. The compiler must be able to find a way to convert one or both of the second and third operands to matching types.
       The conversion rules the compiler uses are fairly complex and may yield surprising results in some cases.*/

    std::cout << (true ? 1 : 2) << '\n';    // okay: both operands have matching type int
    std::cout << (false ? 1 : 2.2) << '\n'; // okay: int value 1 converted to double
    std::cout << (true ? -1 : 2u) << '\n';  // surprising result: -1 converted to unsigned int, result out of range


//RELATIONAL operator

    //floating point values using relational operator can be dangerous

    constexpr double d1{ 100.0 - 99.99 }; // should equal 0.01 mathematically
    constexpr double d2{ 10.0 - 9.99 }; // should equal 0.01 mathematically

    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    else if (d1 > d2)
        std::cout << "d1 > d2" << '\n';
    else if (d1 < d2)
        std::cout << "d1 < d2" << '\n';

    //output:
    //d1 > d2

    /*If you inspect the value of d1 and d2 in a debugger, you’d likely see that d1 = 0.010000000000005116 and
    d2 = 0.0099999999999997868. Both numbers are close to 0.01, but d1 is greater than, and d2 is less than.


    It is safe to compare a floating point literal with a variable of the same type that has been initialized with a
    literal of the same type, so long as the number of significant digits in each literal does not exceed the minimum
    precision for that type. Float has a minimum precision of 6 significant digits, and double has a minimum precision
    of 15 significant digits.

    It is generally not safe to compare floating point literals of different types*/


//LOGICAL operator

    /*
     Logical NOT	!	     !x	      true if x is false, or false if x is true
     Logical AND	&&	    x && y	  true if x and y are both true, false otherwise
     Logical OR	    ||	    x || y	  true if either (or both) x or y are true, false otherwise

    there is also a concept about short circuit evaluation */

    int x{ 5 };
    int y{ 7 };
    if (!x > y)
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';

    //output: 5 is greater than 7

    /*But x is not greater than y, so how is this possible? The answer is that because the logical NOT operator has
    higher precedence than the greater than operator, the expression !x > y actually evaluates as (!x) > y.
    Since x is 5, !x evaluates to 0, and 0 > y is false, so the else statement executes!

    When mixing logical AND and logical OR in a single expression, explicitly parenthesize each operation to
    ensure they evaluate how you intend.

    DE MORGAN's law:
    !(x && y) is equivalent to !x || !y
    !(x || y) is equivalent to !x && !y



    */




    return 0;
}