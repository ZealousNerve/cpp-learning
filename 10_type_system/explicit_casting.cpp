/*C++ supports 5 different types of casts: static_cast, dynamic_cast, const_cast, reinterpret_cast, and C-style casts.
The first four are sometimes referred to as named casts.*/


/*
static_cast      : Compile-time conversion between related types.        (Safe)
dynamic_cast     : Runtime conversion in inheritance hierarchies.        (Safe)
const_cast       : Adds/removes const qualification.                     (Safe only when adding const)
reinterpret_cast : Reinterprets bits as another type.                    (Unsafe)
C-style cast     : Combination of other casts, less explicit.            (Unsafe)

Avoid const_cast and reinterpret_cast unless you have a very good reason to use them.
*/




#include <iostream>

int main(){
    int x { 10 };
    int y { 4 };

//C-STYLED CAST:

    std::cout << (double)x / y << '\n'; // C-style cast of x to double
    std::cout << double(x) / y << '\n'; //  // function-style cast of x to double

    /*A C-style cast does not make it clear which cast(s) will actual be performed, which not only makes your code
    that much harder to understand, but also opens the door for inadvertent misuse. Avoid using C-style casts.

    A C-style cast tries to perform the following C++ casts, in order:
    * const_cast
    * static_cast
    * static_cast, followed by const_cast
    * reinterpret_cast
    * reinterpret_cast, followed by const_cast

    There is one thing you can do with a C-style cast that you can’t do with C++ casts: C-style casts can convert a
    derived object to a base class that is inaccessible (e.g. because it was privately inherited).*/

//STATIC CAST(The C++ style cast):

    // static cast x to a double so we get floating point division
    std::cout << static_cast<double>(x) / y << '\n'; // prints 2.5

    /*static_cast<double>(x) returns a temporary double object containing the converted value 10.0. This temporary is
    then used as the left-operand of the floating point division.

    There are two important properties of static_cast.

    First, static_cast provides compile-time type checking. If we try to convert a value to a type and the compiler
    doesn't know how to perform that conversion, we will get a compilation error.*/

    // a C-style string literal can't be converted to an int, so the following is an invalid conversion
    int z { static_cast<int>("Hello") }; // invalid: will produce compilation error

    /*Second, static_cast is (intentionally) less powerful than a C-style cast, as it will prevent certain kinds of
    dangerous conversions (such as those that require reinterpretation or discarding const).*/


// ============================================================
// CASTING vs TEMPORARY OBJECT INITIALIZATION
// ============================================================

    double x { 9.8 };

    // --- Three ways to convert to int ---

    // 1. static_cast<int>(x)  [PREFERRED]
    //    - Intent is explicit and searchable
    //    - Allows narrowing (you're saying "I know what I'm doing")
    //    - Works with multi-word types (unsigned int, long long, etc.)
    int a { static_cast<int>(x) };           // fine, narrowing allowed

    // 2. int { x }  — direct-list-initialized temporary
    //    - Disallows narrowing → platform-dependent compile errors
    //    - Breaks with multi-word types: unsigned int { x } won't compile
    // int b { int { x } };                  // ERROR: narrowing (double → int)

    // 3. int ( x )  — C-style cast [AVOID]
    //    - Same as static_cast here, but can silently do dangerous casts
    // int c { (int)x };                     // works but risky in general

    std::cout << a << '\n';                  // 9

    // --- Narrowing: why list-init temp fails cross-platform ---
    int p { 10 }, q { 4 };

    // double { p }  → fine on 32-bit int, narrowing error on 64-bit int
    // static_cast   → works everywhere, intent is clear
    std::cout << static_cast<double>(p) / q << '\n';   // 2.5

    // --- Multi-word type restriction ---
    unsigned char c { 'a' };
    // std::cout << unsigned int { c };      // compile ERROR (multi-word)
    std::cout << static_cast<unsigned int>(c) << '\n'; // 97 — fine

    // RULE: Prefer static_cast<T>(x) over T { x } for conversions.
    //List-init is for variables. Casts need explicit intent + no narrowing ban.

    return 0;
}

