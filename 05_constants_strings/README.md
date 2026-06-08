# 05_constants_strings

This chapter explains how to effectively use constants and strings in C++, including best practices for handling input and avoiding common pitfalls.

## Key Concepts
- **std::string** is a dynamic sequence container for characters, allowing modification and storage of text.
- **std::string_view** is a non-owning reference to a string, ideal for read-only operations and avoiding unnecessary copies.
- **C-style strings** are null-terminated arrays of characters, often used with legacy functions and string literals.
- **constexpr** allows string literals to be used in constant expressions, enabling compile-time string manipulation.

## Critical Insights
### Why use `std::getline(std::cin >> std::ws, str)` for line input?
```cpp
// ✅ Correct
std::getline(std::cin >> std::ws, str);

// ❌ Incorrect
std::cin >> str;
```
This matters because `std::cin >> str` leaves the newline character in the input buffer, causing subsequent inputs to fail.

### Why can't you return a local `std::string` as a `std::string_view`?
```cpp
std::string_view getLocalString() {
    std::string local = "hello";
    return local; // ✅ safe
}
```
This is safe because `std::string_view` references the local string, which lives until the function returns.

## What to Remember
⚠️ Never pass `std::string` by value unless you need a copy.  
⚠️ Always cast `.length()` to `int` with `static_cast<int>()` to avoid warnings.  
⚠️ `std::string_view` must never outlive the string it references.