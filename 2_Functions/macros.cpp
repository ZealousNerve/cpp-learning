// In C++, a macro is a rule that defines how input text is converted into replacement output text.
// There are two basic types of macros: object-like macros, and function-like macros(little unsafe).
// neither form ends with a semicolon.

/* The identifier for a macro uses the same naming rules as normal identifiers: 
they can use letters, numbers, and underscores, cannot start with a number, and should not start 
with an underscore. By convention, macro names are typically all uppercase, separated by underscores. 
*/


#include <iostream>
#define MY_NAME "Alex"

int main(){
    std::cout << "My name is: " << MY_NAME << '\n';
    return 0;
}

// The preprocessor converts the above into the following:

int main(){
    std::cout << "My name is: " << "Alex" << '\n';
    return 0;
}


// Avoid macros with substitution text unless no viable alternatives exist.


//CONDITIONAL COMPILATION-------------------------------------------------------

/* The conditional compilation preprocessor directives allow you to specify under what 
conditions something will or won’t compile */

/* The #ifdef preprocessor directive allows the preprocessor to check whether an identifier 
has been previously defined via #define. If so, the code between the #ifdef and matching #endif is compiled. 
If not, the code is ignored. */

#include <iostream>
#define PRINT_JOE
int main(){
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif
    return 0;
}

// #ifndef is the opposite of #ifdef, in that it allows you to check whether an identifier has NOT been #defined yet.

#include <iostream>
int main(){
#ifndef PRINT_BOB
    std::cout << "Bob\n";
#endif
    return 0;
}


/* One more common use of conditional compilation involves using #if 0 
to exclude a block of code from being compiled (as if it were inside a comment block): */

#include <iostream>
int main(){
    std::cout << "Joe\n";

#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    std::cout << "Steve\n";
#endif // until this point
    return 0;
}

//To temporarily re-enable code that has been wrapped in an #if 0, you can change the #if 0 to #if 1: