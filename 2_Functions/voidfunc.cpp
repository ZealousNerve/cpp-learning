// A return statement (with no return value) can be used in a void function(shown below)

#include <iostream>
void printHi()
{
    std::cout << "Hi" << '\n';

    return; 
    //tell compiler to return to the caller -- this is redundant since the return 
    //will happen at the end of the function anyway! function will return to caller here
}   

int main()
{
    printHi(); // okay: function printHi() is called, no value is returned

    //std::cout << printHi(); // compile error as printHi(returns nothing)

    return 0;
}