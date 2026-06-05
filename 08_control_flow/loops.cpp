//The only way to exit an infinite loop is through a return-statement, a break-statement, an exit-statement,
//a goto-statement, an exception being thrown, or the user killing the program.

//Integral loop variables should almost always be signed, as unsigned integers can lead to unexpected issues.


/*

   for (;;)
      statement;//this will run a endless loop

*/

#include <iostream>
int breakOrReturn(); //forward declaration for upcoming theories

int main(){
    int i{ 0 };
    for ( ; i < 10; ){ // no init-statement or end-expression
        std::cout << i << ' ';
        ++i;
    }

    /*Rather than having the for loop do the initialization and incrementing, we’ve done it manually. We have done so
    purely for academic purposes in this example, but there are cases where not defining a loop variable (because
    you already have one) or not incrementing it in the end-expression (because you’re incrementing it some other
    way) is desired.*/

    std::cout << '\n';


    /*Although for-loops typically iterate over only one variable, sometimes for-loops need to work with multiple
    variables. To assist with this, the programmer can define multiple variables in the init-statement,
    and can make use of the comma operator to change the value of multiple variables in the end-expression:*/

    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';


    /*The break statement causes a while loop, do-while loop, for loop, or switch statement to end, with execution
    continuing with the next statement after the loop or switch being broken out of.*/

    //see the below function first
    int returnValue{ breakOrReturn() };
    std::cout << "Function breakOrReturn returned " << returnValue << '\n';

    return 0;
}


int breakOrReturn(){
    while (true){ // infinite loop
        std::cout << "Enter 'b' to break or 'r' to return: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'b')
            break; // execution will continue at the first statement beyond the loop

        if (ch == 'r')
            return 1; // return will cause the function to immediately return to the caller (in this case, main())
    }

    // breaking the loop causes execution to resume here

    std::cout << "We broke out of the loop\n";

    return 0;
}




//The continue statement provides a convenient way to end the current iteration of a loop without terminating the entire loop.


