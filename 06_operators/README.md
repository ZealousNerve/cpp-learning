# 06_operators

## Key Concepts

- Logical XOR can be simulated using `!=` with boolean conversions.
- C++ does not have a built-in logical XOR operator, but `!=` works on booleans.
- The comma operator allows multiple expressions to be evaluated in one statement.
- The conditional operator `?:` provides a ternary form of `if-else`.
- Relational operators can be dangerous with floating-point numbers due to precision issues.
- Logical operators `!`, `&&`, and `||` have short-circuit evaluation behavior.
- Operator precedence and associativity determine the order of evaluation in expressions.
- The `pow` function from `<cmath>` is used for exponentiation in C++.

## Critical Insights

### ❌ Bitwise XOR is not logical XOR
```cpp
int a = 5, b = 3;
int result = a ^ b; // 6 (binary 110)
```

### ✅ Logical XOR using `!=` with boolean conversion
```cpp
bool a = true, b = false;
bool result = a != b; // true
```

### ❌ Precedence can change meaning of expressions
```cpp
if (!x > y) { /* ... */ }
// Evaluates as (!x) > y, not !(x > y)
```

## Files in this Chapter

| File | What it demonstrates |
|------|----------------------|
| precedence_associativity.cpp | Operator precedence and associativity table |
| other_operators.cpp | Comma operator, conditional operator, and logical operators |
| logical_xor.cpp | Simulating logical XOR using `!=` |

## What to Remember

- Use `!=` with boolean conversions for logical XOR.
- Parenthesize complex expressions to avoid precedence errors.
- Be cautious with floating-point comparisons using relational operators.