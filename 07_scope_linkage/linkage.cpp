//INTERNAL LINKAGE======================================================================================================

/*in previous topic we found that local variables have no linkage at all, but global variables and function identifier
have either internal linkage or external linkage*/

/*An identifier with internal linkage can be seen and used within a single translation unit, but it is not accessible
from other translation units. This means that if two source files have identically named identifiers with internal
linkage, those identifiers will be treated as independent (and do not result in an ODR violation for having
duplicate definitions).*/

//Global variables with internal linkage

/*Global variables with internal linkage are sometimes called internal variables. To make a non-constant global
variable internal, we use the static keyword.*/

#include <iostream>
static int g_x{};
 /*non-constant globals have external linkage by default, but can be given internal linkage via the
static keyword, and now this g_x will be visible only in the same file*/

//Because g_x is internal to each file, main.cpp has no idea that a.cpp also has a variable named g_x (and vice versa).

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{
    std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
    return 0;
}

/*Const and constexpr global variables have internal linkage by default (and thus don’t need the static
keyword -- if it is used, it will be ignored).*/

/*The use of the static keyword above is an example of a storage class specifier, which sets both the name’s linkage
 and its storage duration. The most commonly used storage class specifiers are static, extern, and mutable.
 The term storage class specifier is mostly used in technical documentations.*/

[[maybe_unused]] static int add(int x, int y)
{
    return x + y;
}

/*As noted above, function identifiers also have linkage. Functions default to external linkage, but can be set
to internal linkage via the static keyword:

This function is declared as static, and can now be used only within this file. Attempts to access it from another
file via a function forward declaration will fail*/


/*
In modern C++, use of the static keyword for giving identifiers internal linkage is falling out of favor.
Unnamed namespaces can give internal linkage to a wider range of identifiers (e.g. type identifiers),
and they are better suited for giving many identifiers internal linkage.


There are typically two reasons to give identifiers internal linkage:

1. There is an identifier we want to make sure isn’t accessible to other files. This could be a global variable we
    don’t want messed with, or a helper function we don’t want to be called.

2. To be pedantic about avoiding naming collisions. Because identifiers with internal linkage aren’t exposed to the
    linker, they can only collide with names in the same translation unit, not across the entire program.*/


//EXTERNAL LINKAGE:=====================================================================================================

/*An identifier with external linkage can be seen and used both from the file in which it is defined, and from other
code files (via a forward declaration). In this sense, identifiers with external linkage are truly “global” in that
they can be used anywhere in your program!*/

/*function have by default external linkage so that's why they can be called from different files with the help of
forward declaration*/

/*Global variables with external linkage are sometimes called external variables. To make a global variable
external (and thus accessible by other files), we can use the extern keyword to do so:*/

//------------------------------a.cpp--------------------------------------------------------------
int g_p { 2 }; // non-constant globals are external by default (no need to use extern)
extern const int g_q { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_r { 3 }; // constexpr globals can be defined as extern, making them external
//---------------------------------a.cpp------------------------------------------------------------

/*Although constexpr variables can be given external linkage via the extern keyword, they can not be forward declared
as constexpr. This is because the compiler needs to know the value of the constexpr variable (at compile time).
If that value is defined in some other file, the compiler has no visibility on what value was defined in that other file.

However, you can forward declare a constexpr variable as const, which the compiler will treat as a runtime const.
This isn’t particularly useful.*/

//-------------------------------main.cpp----------------------------------------------------------------
extern int g_p;       // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_q; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else
//-----------------------------------main.cpp---------------------------------------------------------

//as we can see above same extern keyword is used in two cases, the first case is when we wanted to create a external linkage
//and second when we wanted to forward declare those identifiers, but function forward declaration doesn't need extern

