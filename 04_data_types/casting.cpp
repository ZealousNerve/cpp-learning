//When the compiler does type conversion on our behalf without us explicitly asking, we call this implicit type conversion

/*

the conversion does not change variable y from type int to double or the value of y from 5 to 5.0. Instead,
the conversion uses the value of y (5) as input, and returns a temporary object of type double with value 5.0.
This temporary object is then passed to function print.

Some advanced type conversions (e.g. those involving const_cast or reinterpret_cast) do not return temporary objects,
but instead reinterpret the type of existing value or object.

Explicit type conversion allow us (the programmer) to explicitly tell the compiler to convert a value from one type
to another type


To perform an explicit type conversion, in most cases we’ll use the static_cast operator.
The syntax for the static cast looks a little funny:

static_cast<new_type>(expression)

*/

#include <iostream>
void print(int x){
    std::cout << x << '\n';
}

int main(){
    print( static_cast<int>(5.5) ); // explicitly convert double value 5.5 to an int
    return 0;
}


/*suppose we want to do type conversion from unsigned int to signed or vice versa, and if there is an issue in range
 like, 5 is same in both types, but if out of range then there will be a problem, and that will be solved by modulo wrapping
 */

#include <iostream>


int s { -1 };
std::cout << static_cast<unsigned int>(s) << '\n'; // prints 4294967295

unsigned int u { 4294967295 }; // largest 32-bit unsigned int
std::cout << static_cast<int>(u) << '\n'; // implementation-defined prior to C++20, -1 as of C++20

return 0;
