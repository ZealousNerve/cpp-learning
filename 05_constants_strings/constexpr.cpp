/*
A const variable with an integral type and a constant expression initializer can be used in a constant expression.
All other const variables cannot be used in constant expressions. but just using const keyword not sure that it can be
used in the constant expression or not, there are certain challenges:

as you can see in examples given below,
 */

int a { 5 };       // not const at all
const int b { a }; // clearly not a constant expression (since initializer is non-const)
const int c { 5 }; // clearly a constant expression (since initializer is a constant expression)

const int d { someVar };    // not obvious whether d is usable in a constant expression or not
const int e { getValue() }; // not obvious whether e is usable in a constant expression or not

/*
here in last two examples above, we are not sure, as to use d in constant expression, we need to be sure that someVar is
a constant, if someVar is initialize with some function call or variable then we have to inspect those also

one major issue is that non integral constant variables are also cannot be used in constant expression, but many a times
we want to use non integral const also

and to solve all these problems we have constexpr keyword(shorthand for constant expression)

a constexpr variable is always a compile time constant, and that's why this needs to be initialized with a constant only
otherwise we will get a compilation error
*/

#include <iostream>

// The return value of a non-constexpr function is not constexpr
int five(){
 return 5;
}

int main(){
 constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
 //as you can see above constexpr works for variables with non-integral types also
 constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
 constexpr int something { sum };  // ok: sum is a constant expression

 std::cout << "Enter your age: ";
 int age{};
 std::cin >> age;

 constexpr int myAge { age };      // compile error: age is not a constant expression
 constexpr int f { five() };       // compile error: return value of five() is not constexpr

 /*Because functions normally execute at runtime, the return value of a function is not constexpr
 (even when the return expression is a constant expression). This is why five() is not a legal initialization value for constexpr int f.*/

 return 0;
}


/*
DIFFERENCE (const vs constexpr)

1. const means that the value of an object cannot be changed after initialization. The value of the initializer may be
known at compile-time or runtime. The const object can be evaluated at runtime.

2. constexpr means that the object can be used in a constant expression. The value of the initializer must be known
at compile-time. The constexpr object can be evaluated at runtime or compile-time

Constexpr variables are implicitly const. Const variables are not implicitly constexpr
(except for const integral variables with a constant expression initializer)

*/



/*
CONSTEXPR FUNCTION:

A constexpr function is a function that can be called in a constant expression. A constexpr function must evaluate
at compile-time when the constant expression it is part of must evaluate at compile time (e.g. in the initializer
of a constexpr variable). Otherwise, a constexpr function may be evaluated at either compile-time (if eligible)
or runtime. To be eligible for compile-time execution, all arguments must be constant expressions

 */

#include <iostream>

int max(int x, int y){ // this is a non-constexpr function
 if (x > y)
  return x;
 else
  return y;
}

constexpr int cmax(int x, int y){ // this is a constexpr function
 if (x > y)
  return x;
 else
  return y;
}

int main(){
 int m1 { max(5, 6) };            // ok
 const int m2 { max(5, 6) };      // ok
 constexpr int m3 { max(5, 6) };  // compile error: max(5, 6) not a constant expression

 int m4 { cmax(5, 6) };           // ok: may evaluate at compile-time or runtime
 const int m5 { cmax(5, 6) };     // ok: may evaluate at compile-time or runtime
 constexpr int m6 { cmax(5, 6) }; // okay: must evaluate at compile-time

 return 0;
}