
# Chapter: Data Types and Characters

## Key Concepts
- Understanding integer types and their ranges
- Using fixed-point and floating-point types
- Working with character types and ASCII values
- Handling input/output with `std::cin` and `std::cout`
- Using escape sequences for special characters
- Working with boolean types and input/output flags

## Critical Insights

```cpp
// ❌ Narrowing conversion error
bool bNo{2}; // error: narrowing conversions disallowed

// ✅ Allowed with copy initialization
bool bNo = 2; // okay: initialized to true
```

```cpp
// ❌ Default behavior of std::cin with bool
std::cin >> b; // only accepts 0 or 1

// ✅ Allow input of 'true' or 'false'
std::cin >> std::boolalpha >> b;
```

```cpp
// ❌ Default behavior of std::cout with bool
std::cout << true << '\n'; // prints 1

// ✅ Print bools as true/false
std::cout << std::boolalpha << true << '\n'; // prints true
```

## Files in this Chapter
| File | What it demonstrates |
|------|----------------------|
| data_types.cpp | Integer, floating-point, and boolean types |
| characters.cpp | Character types, ASCII values, and escape sequences |
| input_output.cpp | Input/output with `std::cin` and `std::cout` |

## What to Remember
- Avoid narrowing conversions when initializing variables
- Use `std::boolalpha` to read and print boolean values as words
- Be aware of ASCII values and escape sequences for special characters