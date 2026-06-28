#include <iostream>

//LOCAL VARIABLES:------------------------------------------------------------------------------------------------------

/*Local variables have block scope, which means they are in scope from their point of definition to the end of the
block they are defined within.*/

/*Although function parameters are not defined inside the function body, for typical functions they can be
considered to be part of the scope of the function body block.*/

/*Identifiers have another property named linkage. An identifier’s linkage determines whether a declaration of that
same identifier in a different scope refers to the same object (or function).

Local variables have no linkage. Each declaration of an identifier with no linkage refers to a unique object or function.*/

int main(){
    int x {2}; // local variable, no linkage
    {
        int x {3}; // this declaration of x refers to a different object than the previous x, despite being in the same scope
    }
    return 0;
}


/*local variables have automatic duration by default, which means they are created at the point of definition, and
destroyed when the block is exited.

Using the static keyword on a local variable changes its duration from automatic duration to static duration.
This means the variable is now created at the start of the program, and destroyed at the end of the program
(just like a global variable). As a result, the static variable will retain its value even after it goes out of scope!


Static local variables can be made const (or constexpr). One good use for a const static local variable is when you
have a function that needs to use a const value, but creating or initializing the object is expensive (e.g. you need
to read the value from a database). If you used a normal local variable, the variable would be created and initialized
every time the function was executed. With a const/constexpr static local variable, you can create and initialize the
expensive object once, and then reuse it whenever the function is called.*/



//----------------------------------------------------------------------------------------------------------------------




//GLOBAL VARIABLE:------------------------------------------------------------------------------------------------------
    //declared and defined outside in global namespace just after includes and all as seen at the top of the code

    //Global variables are created when the program starts (before main() begins execution), and destroyed when it ends.
    //This is called static duration. Variables with static duration are sometimes called static variables.

    //Consider using a “g” or “g_” prefix when naming global variables (especially those defined in the global namespace),
    //to help differentiate them from local variables and function parameters.


    int g_x;       // no explicit initializer (zero-initialized by default)
    int g_y {};    // value initialized (resulting in zero-initialization)
    int g_z { 1 }; // list initialized with specific value


    int gb {}; // global variable gb, we will see later in the code
    const int g_c { 1 };     // const global variable g_c, initialized with a value
    constexpr int g_d { 2 }; // constexpr global variable g_d, initialized with a value


//----------------------------------------------------------------------------------------------------------------------


//VARIABLE SHADOWING:---------------------------------------------------------------------------------------------------


/*Each block defines its own scope region. So what happens when we have a variable inside a nested block that has the
same name as a variable in an outer block? When this happens, the nested variable “hides” the outer variable in areas
where they are both in scope. This is called name hiding or shadowing.*/

int main(){ // outer block
        int apples { 5 }; // here's the outer block apples

        { // nested block
            // apples refers to outer block apples here
            std::cout << apples << '\n'; // print value of outer block apples

            int apples{ 0 }; // define apples in the scope of the nested block

            // apples now refers to the nested block apples
            // the outer block apples is temporarily hidden

            apples = 10; // this assigns value 10 to nested block apples, not outer block apples

            std::cout << apples << '\n'; // print value of nested block apples
        } // nested block apples destroyed


        std::cout << apples << '\n'; // prints value of outer block apples

        return 0;
    } // outer block apples destroyed


/*Similar to how variables in a nested block can shadow variables in an outer block, local variables with the same name
as a global variable will shadow the global variable wherever the local variable is in scope:

but we can use scope resolution operator with no namespace identifier to call the global variable inside that scope

avoid variable shadowing*/



/*Duration summary:-

A variable’s duration determines when it is created and destroyed.

1. Variables with automatic duration are created at the point of definition, and destroyed when the block they are part of is exited. This includes:
    a. Local variables
    b. Function parameters
2. Variables with static duration are created when the program begins and destroyed when the program ends. This includes:
    a. Global variables
    b. Static local variables
3. Variables with dynamic duration are created and destroyed by programmer request. This includes:
    a. Dynamically allocated variables*/