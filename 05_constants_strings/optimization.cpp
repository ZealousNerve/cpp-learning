/*
Optimization is the process of improving a program so it runs faster and uses fewer resources. Modern C++
compilers can automatically optimize code during compilation, allowing programmers to focus on writing clean
and readable code while still achieving good performance.
*/

#include <iostream>
//as-if rules
// --- 1. CONSTANT FOLDING ---
// Compiler replaces (3 + 4) with 7 at compile time. No runtime addition happens.
void constant_folding() {
    int x { 3 + 4 };       // optimizer sees this as: int x { 7 };
    std::cout << x << '\n';
}

// --- 2. CONSTANT PROPAGATION ---
// Compiler knows x = 7, replaces usage of x with 7 directly.
void constant_propagation() {
    const int x { 7 };
    const int y { 3 };
    std::cout << x + y << '\n'; // becomes: cout << 10 (folding after propagation)
}

// --- 3. DEAD CODE ELIMINATION ---
// 'unused' is never used → compiler removes it entirely in Release mode.
void dead_code_elimination() {
    const int unused { 42 };    // optimized OUT
    const int used   { 10 };
    std::cout << used << '\n';
}

int main() {
    constant_folding();
    constant_propagation();
    dead_code_elimination();
    return 0;
}


//For daily learning, stay in Debug. Switch to Release only when you want to experiment with optimization behavior
/*

Flag    Meaning
-O0     No optimization (default debug)
-O1     Basic optimization
-O2     Moderate optimization (common release)
-O3     Aggressive optimization
-Os     Optimize for binary size

 */


const double x { 1.2 };
const double y { 3.4 };
const double z { x + y }; // x + y may evaluate at runtime or compile-time

/*
The expression x + y would normally evaluate at runtime, but since the value of x and y are known at compile-time,
the compiler may opt to perform compile-time evaluation instead and initialize z with the compile-time calculated value 4.6.
*/

/*
In a few other cases, the C++ language requires an expression that can be evaluated at compile-time. For example,
constexpr variables require an initializer that can be evaluated at compile-time:
*/

constexpr int x { expr }; // Because variable x is constexpr, expr must be evaluatable at compile-time




/*

the standard defines a “constant expression”, which is an expression that must be evaluatable at compile-time,
along with rules that determine how the compiler should handle these expressions.

An expression that is not a constant expression is often called a non-constant expression, and may informally be
called a runtime expression (as such expressions typically evaluate at runtime).

 */

#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // this return expression is a runtime expression
}

// The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five()
{
    return 5;      // this return expression is a constant expression
}

int main()
{
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // The return values of non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though the return expression is a constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    return 0;
}

/*The compiler is only required to evaluate constant expressions at compile-time in contexts that require a constant
expression. It may or may not do so in other cases.*/


