#include <iostream>
#include <string>
#include <string_view> //to use string_view;

void printString(std::string str){
    std::cout << str << '\n';
}

void printSV(std::string_view str)
{
    std::cout << str << '\n';
}

int main(){
    int x { 5 }; // x makes a copy of its initializer
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    std::cout << s << " " << x << '\n';

    /*When s is initialized, the C-style string literal "Hello, world!" is copied into memory allocated for
    std::string s. Unlike fundamental types, initializing and copying a std::string is slow.

    In the above program, all we do with s is print the value to the console, and then s is destroyed.
    We’ve essentially made a copy of “Hello, world!” just to print and then destroy that copy. That’s inefficient.

    C++17 introduced std::string_view (which lives in the <string_view> header). std::string_view provides
    read-only access to an existing string (a C-style string, a std::string, or another std::string_view)
    without making a copy.

    Prefer std::string_view over std::string when you need a read-only string, especially for function parameters.*/

    std::string_view s1 { "Hello, world!" }; // initialize with C-style string literal
    std::cout << s1 << '\n';

    std::string s0{ "Hello, world!" };
    std::string_view s2 { s0 };  // initialize with std::string
    std::cout << s2 << '\n';

    std::string_view s3 { s2 }; // initialize with std::string_view
    std::cout << s3 << '\n';

    /*Because std::string makes a copy of its initializer (which is expensive), C++ won’t allow implicit conversion
    of a std::string_view to a std::string

    but if we want to, then we can do it explicitly in two ways
    1. Explicitly create a std::string with a std::string_view initializer (which is allowed, since this will
       rarely be done unintentionally)
    2. Convert an existing std::string_view to a std::string using static_cast*/

    std::string_view sv{ "Hello, world!" };
    // printString(sv);   // compile error: won't implicitly convert std::string_view to a std::string
    std::string s4{ sv }; // okay: we can create std::string using std::string_view initializer
    printString(s4);      // and call the function with the std::string
    printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string


    //literal for string_view
    using namespace std::string_literals;      // access the s suffix
    using namespace std::string_view_literals; // access the sv suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

    //Unlike std::string, std::string_view has full support for constexpr:

    constexpr std::string_view s5{ "Hello, world!" }; // s is a string symbolic constant
    std::cout << s5 << '\n'; // s will be replaced with "Hello, world!" at compile-time

    return 0;
}


//A quick guide on when to use std::string vs std::string_view

/*
=========================================================
std::string vs std::string_view Quick Reference
=========================================================

VARIABLES

Use std::string when:
- You need a string that can be modified.
- You need to store user input.
- You need to store the return value of a function
  that returns std::string.

Use std::string_view when:
- You need read-only access to an existing string.
- You need a symbolic constant for a C-style string.
- You need to view the return value of a function
  returning a C-style string or a valid std::string_view.

---------------------------------------------------------
FUNCTION PARAMETERS
---------------------------------------------------------

Use std::string when:
- The function must modify a copy of the argument
  without affecting the caller (rare).
- Using C++14 or older and avoiding references.

Use std::string_view when:
- The function only needs read-only access.
- The function should work with non-null-terminated strings.

---------------------------------------------------------
RETURN TYPES
---------------------------------------------------------

Use std::string when:
- Returning a local std::string.
- Returning a std::string parameter.
- Returning a function call/operator result that
  produces std::string by value.

Use std::string_view when:
- Returning a string literal.
- Returning a local std::string_view initialized from
  a string literal.
- Returning a std::string_view parameter.

---------------------------------------------------------
IMPORTANT NOTES
---------------------------------------------------------

std::string:
- Initialization and copying can be expensive.
- Avoid passing by value when unnecessary.
- Avoid creating short-lived temporary strings.
- Modifying a string invalidates all views to it.
- Returning a local std::string by value is safe.

std::string_view:
- Primarily used for function parameters and
  returning string literals.
- String literals have static lifetime, so views
  to them are always safe.
- Destroying the original string invalidates all views.
- Using an invalidated view causes undefined behavior.
- A std::string_view may not be null-terminated.

=========================================================
*/


