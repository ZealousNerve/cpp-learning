//function cannot be nested in cpp, means we can't define function inside a function

/* 
In C++, there are two special requirements for main():
    1. main() is required to return an int.
    2. Explicit function calls to main() are disallowed. 
    
*/

//C does allow main() to be called explicitly, so some C++ compilers will allow this for compatibility reasons.

/* It is a common misconception that main is always the first function that executes.
Global variables are initialized prior to the execution of main. If the initializer 
for such a variable invokes a function, then that function will execute prior to main */

/* The return value from main() is sometimes called a status code (or less commonly, an exit code,
or rarely a return code). The status code is used to signal whether your program was successful or not.
By convention, a status code of 0 means the program ran normally */


/* The C++ standard only defines the meaning of 3 status codes: 0, EXIT_SUCCESS, and EXIT_FAILURE. 
0 and EXIT_SUCCESS both mean the program executed successfully. EXIT_FAILURE means the program 
did not execute successfully. */

#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE

int main()
{
    return EXIT_FAILURE;
}

//Failure to return a value from a value-returning function will cause undefined behavior.
//only function main() is a exception to above line
//The function main() will implicitly return the value 0 if no return statement is provided.
//A value-returning function can only return a single value back to the caller each time it is called.