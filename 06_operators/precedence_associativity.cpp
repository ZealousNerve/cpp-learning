/*precedence decide which operator will be evaluated first, and associativity at each precedence level comes into
action when operator with same precedence are adjacent to each other, or same operator are adjacent, then associativity
like left to right or right to left if deciding factor

in 7 - 4 - 1
adjacent operator is same so subtraction have left to right associativity and hence it will be evaluated from left to
right, (7-4)-1 = 2*/

/*
=============================================================
  OPERATOR PRECEDENCE & ASSOCIATIVITY TABLE (C++)
  Lower number = Higher precedence (1 is highest, 17 is lowest)
  L->R = Left to Right associativity
  R->L = Right to Left associativity
=============================================================

Prec | Assoc | Operator(s)                          | Description
-----|-------|--------------------------------------|---------------------------
  1  | L->R  | ::                                   | Global scope (unary)
     |       | ::                                   | Namespace scope (binary)
-----|-------|--------------------------------------|---------------------------
  2  | L->R  | ()                                   | Parentheses
     |       | ()                                   | Function call
     |       | type()                               | Functional cast
     |       | type{}                               | List init temp object (C++11)
     |       | []                                   | Array subscript
     |       | .                                    | Member access from object
     |       | ->                                   | Member access from object ptr
     |       | ++                                   | Post-increment
     |       | --                                   | Post-decrement
     |       | typeid                               | Run-time type information
     |       | const_cast                           | Cast away const
     |       | dynamic_cast                         | Run-time type-checked cast
     |       | reinterpret_cast                     | Cast one type to another
     |       | static_cast                          | Compile-time type-checked cast
     |       | sizeof...                            | Get parameter pack size
     |       | noexcept                             | Compile-time exception check
     |       | alignof                              | Get type alignment
-----|-------|--------------------------------------|---------------------------
  3  | R->L  | +                                    | Unary plus
     |       | -                                    | Unary minus
     |       | ++                                   | Pre-increment
     |       | --                                   | Pre-decrement
     |       | !  / not                             | Logical NOT
     |       | ~                                    | Bitwise NOT
     |       | (type)                               | C-style cast
     |       | sizeof                               | Size in bytes
     |       | co_await                             | Await async call (C++20)
     |       | &                                    | Address of
     |       | *                                    | Dereference
     |       | new  / new[]                         | Dynamic memory allocation
     |       | delete / delete[]                    | Dynamic memory deletion
-----|-------|--------------------------------------|---------------------------
  4  | L->R  | ->*                                  | Member pointer selector
     |       | .*                                   | Member object selector
-----|-------|--------------------------------------|---------------------------
  5  | L->R  | *   /   %                            | Multiply, Divide, Remainder
-----|-------|--------------------------------------|---------------------------
  6  | L->R  | +   -                                | Addition, Subtraction
-----|-------|--------------------------------------|---------------------------
  7  | L->R  | <<  >>                               | Bitwise shift left / right
-----|-------|--------------------------------------|---------------------------
  8  | L->R  | <=>                                  | Three-way comparison (C++20)
-----|-------|--------------------------------------|---------------------------
  9  | L->R  | <   <=   >   >=                      | Comparison operators
-----|-------|--------------------------------------|---------------------------
 10  | L->R  | ==  !=                               | Equality, Inequality
-----|-------|--------------------------------------|---------------------------
 11  | L->R  | &                                    | Bitwise AND
-----|-------|--------------------------------------|---------------------------
 12  | L->R  | ^                                    | Bitwise XOR
-----|-------|--------------------------------------|---------------------------
 13  | L->R  | |                                    | Bitwise OR
-----|-------|--------------------------------------|---------------------------
 14  | L->R  | &&  / and                            | Logical AND
-----|-------|--------------------------------------|---------------------------
 15  | L->R  | ||  / or                             | Logical OR
-----|-------|--------------------------------------|---------------------------
 16  | R->L  | throw                                | Throw expression
     |       | co_yield                             | Yield expression (C++20)
     |       | ?:                                   | Conditional (ternary)
     |       | =                                    | Assignment
     |       | *=  /=  %=  +=  -=                  | Arithmetic assignment
     |       | <<=  >>=                             | Bitwise shift assignment
     |       | &=  |=  ^=                           | Bitwise assignment
-----|-------|--------------------------------------|---------------------------
 17  | L->R  | ,                                    | Comma operator
-----|-------|--------------------------------------|---------------------------

KEY NOTES:
  - No exponent operator in C++ (^ is Bitwise XOR, not power)
  - Use std::pow() for exponentiation
  - Precedence ≠ Order of evaluation of operands (operands can eval in any order)
  - Best practice: parenthesize all non-trivial compound expressions
  - Exception: single assignment RHS does NOT need parentheses
  - << handles both bitwise shift AND insertion (cout)
  - >> handles both bitwise shift AND extraction (cin)
  - Compiler determines which based on operand types

QUICK MEMORY AID (most used, top to bottom):
  Scope :: > Postfix ++ -- > Unary * & > * / % > + - >
  << >> > Comparisons > == != > & > ^ > | > && > || >
  Ternary ?: = (assignments) > Comma ,
=============================================================
*/


//C++ doesn’t include an operator to do exponentiation (operator^ has a different function in C++)

/*Use parentheses to make it clear how a non-trivial compound expression should evaluate
because we can't remember precedence table(even if they are technically unnecessary).*/

