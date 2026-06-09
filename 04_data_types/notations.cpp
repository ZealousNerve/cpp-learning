//SCIENTIFIC NOTATION---------------------------------

//Numbers in scientific notation take the following form: significand x 10exponent. For example,
//the scientific notation 1.2 x 10⁴

//1.2 x 10⁴ would be written as 1.2e4
//5e-2 is equivalent to 5 * 10⁻²

//SIGNIFICANT DIGITS------------------------------------

//The digits in the significand (the part before the ‘e’) are called the significant digits (or significant figures).
//The more significant digits, the more precise a number is.
//3.14159 would be written as 3.14159e0. Since there are 6 numbers in the significand, this number has 6 significant digits.

/*
For numbers with no decimal point, trailing zeros are considered to be insignificant by default.
Given the number 2100 (with no additional information), we assume the trailing zeroes are not significant, so we drop them:

2100 = 2.1e3 (trailing zeros assumed not significant)

However, if we happened to know that this number was measured precisely (or that the actual number was somewhere
between 2099.5 and 2100.5), then we should instead treat those zeros as significant:

2100 = 2.100e3 (trailing zeros known significant)
 */


//When using floating point literals, always include at least one decimal place (even if the decimal is 0).
//This helps the compiler understand that the number is a floating point number and not an integer.

//Note that by default, floating point literals default to type double. An f suffix is used to denote a literal of type float.

//By default, std::cout will not print the fractional part of a number if the fractional part is 0.

/*When outputting floating point numbers, std::cout has a default precision of 6 -- that is, it assumes all floating
point variables are only significant to 6 digits (the minimum precision of a float), and hence it will truncate
anything after that.

9.87654e+006 is the same as 9.87654e6
*/

/*
We can override the default precision that std::cout shows by using an output manipulator function named
std::setprecision(). Output manipulators alter how data is output, and are defined in the iomanip header.
 */

#include <iomanip> // for output manipulator std::setprecision()
#include <iostream>

int main()
{
 std::cout << std::setprecision(17); // show 17 digits of precision
 std::cout << 3.33333333333333333333333333333333333333f <<'\n'; // f suffix means float
 std::cout << 3.33333333333333333333333333333333333333 << '\n'; // no suffix means double

 return 0;
}

// Outputs:
// 3.3333332538604736
// 3.3333333333333335