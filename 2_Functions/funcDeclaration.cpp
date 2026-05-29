#include <iostream>

int add(int x, int y); // forward declaration of add() (using a function declaration)

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // this works because we forward declared add() above
    return 0;
}

int add(int x, int y) // even though the body of add() isn't defined until here
{
    return x + y;
}


// int add(int, int); // valid function declaration

/* forward declarations are used to tell the compiler about the existence of some function 
that has been defined in a different code file. Reordering isn’t possible in this scenario
because the caller and the callee are in completely different files! */


/* there are times when we have two functions that call each other. Reordering isn’t possible
in this case either, as there is no way to reorder the functions such that each is before the other.
Forward declarations give us a way to resolve such circular dependencies. */