//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
// Null Statement ( ; )

// A null statement is just a semicolon.
// It is a valid statement that does nothing.

// Example:
#include <cmath>
#include <iostream>
void doSomething() {}
int main(){
    int x{5};
    if (x > 10)
        ;   // do nothing

    // Common Bug:
    if (x>10);   // <-- accidental ';'
    doSomething();

    // Equivalent to:
    if (x>10)
        ;   // null statement

    doSomething();    // always executes

// Notes:
// • ';' alone = null statement.
// • Used when a statement is required but no action is needed.
// • Commonly used in loops.
// • Avoid placing ';' after if(...), unless intentional.

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

//constexpr if: suppose if the condition inside the if is a const expression, then that condition can be evaluated at
//compile time, and to do so we make that conditional statement a constexpr, the syntax are as follows

    constexpr double gravity{ 9.8 };
    if constexpr (gravity == 9.8) // now using constexpr if
        std::cout << "Gravity is normal.\n";
    else
        std::cout << "We are not on Earth.\n";


    /*For optimization purposes, modern compilers will generally treat non-constexpr if-statements that have constexpr
     *conditionals as if they were constexpr-if-statements. However, they are not required to do so.

    A compiler that encounters a non-constexpr if-statement with a constexpr conditional may issue a warning advising
    you to use if constexpr instead. This will ensure that compile-time evaluation will occur (even if optimizations
    are disabled).*/


    //GOTO statement
    double y{};
    tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> y;

    if (y < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(y) << '\n';

    /*In this program, the user is asked to enter a non-negative number. However, if a negative number is entered,
    the program utilizes a goto statement to jump back to the tryAgain label. The user is then asked again to enter
    a new number. In this way, we can continually ask the user for input until he or she enters something valid.

    we covered two kinds of scope: local (block) scope, and file (global) scope. Statement labels utilize a third kind
    of scope: function scope, which means the label is visible throughout the function even before its point of
    declaration. The goto statement and its corresponding statement label must appear in the same function.

    Avoid goto statements (unless the alternatives are significantly worse for code readability).*/


    return 0;
}