# 06_operators

This chapter explores C++ operators, their types, and how they enable essential operations like arithmetic, comparison, and logical processing.

## Key Concepts
- **Arithmetic operators** (`+`, `-`, `*`, `/`, `%`) perform basic mathematical operations on numeric values.
- **Comparison operators** (`<`, `>`, `<=`, `>=`, `==`, `!=`) evaluate relationships between operands and return boolean results.
- **Logical operators** (`&&`, `||`, `!`) combine or negate boolean expressions to control program flow.
- **Bitwise operators** (`<<`, `>>`, `&`, `|`, `^`, `~`) manipulate individual bits of integers for low-level operations.
- **Assignment operators** (`=`, `+=`, `-=` etc.) assign values to variables and can also perform operations.
- **Conditional operator** (`?:`) provides a shorthand for `if-else` statements by returning a value based on a condition.
- **Comma operator** (`,`) allows multiple expressions to be evaluated in sequence, with the result of the last expression being returned.
- **Shift operators** (`<<`, `>>`) shift the bits of a number left or right, often used for efficient multiplication/division by powers of two.
- **Ternary operator** (`?:`) is a shorthand for `if-else` that returns a value based on a condition.
- **Operator precedence** determines the order in which operators are evaluated in complex expressions.

## Critical Insights
### Operator precedence vs. order of evaluation
```cpp
int a = 5 + 3 * 2; // Result is 11, not 16
```
Operator precedence dictates that multiplication occurs before addition, which can lead to unexpected results if not understood.

### Bitwise vs. logical operators
```cpp
int a = 5 & 3; // Result is 1 (binary 01 & 01)
bool b = (5 && 3); // Result is true
```
Bitwise operators work on individual bits, while logical operators evaluate boolean expressions, leading to different outcomes.

## What to Remember
⚠️ **Precedence ≠ evaluation order** — parentheses are essential to enforce the desired sequence of operations.  
⚠️ **Avoid using `^` for exponentiation** — it represents bitwise XOR, not power. Use `std::pow()` instead.  
⚠️ **Use `==` for comparison, not `=`** — the latter assigns values and can lead to logical errors in conditionals.