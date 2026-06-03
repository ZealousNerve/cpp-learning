paused

# Literals, Strings, and String Views

## Key Concepts
- **Literals**: Understand how to use various C++ literals (integer, floating-point, character, string) and their suffixes.
- **Strings**: Learn about `std::string` and its usage, including input handling with `std::getline()` and string manipulation.
- **String Views**: Explore `std::string_view` and its benefits for read-only string access without copying.
- **String Literals**: Recognize the difference between C-style string literals and `std::string`/`std::string_view` literals.
- **Suffixes**: Use `s` for `std::string` literals and `sv` for `std::string_view` literals.
- **Performance**: Understand when to use `std::string` vs `std::string_view` for efficiency and correctness.

## Critical Insights
```cpp
// ❌ Avoid passing std::string by value
void badFunction(std::string s) { /* ... */ }

// ✅ Prefer passing by const reference
void goodFunction(const std::string& s) { /* ... */ }
```

```cpp
// ❌ Don't use std::string for read-only access
void process(const std::string& s) { /* ... */ }

// ✅ Use std::string_view for read-only access
void process(std::string_view s) { /* ... */ }
```

```cpp
// ✅ Use string_view for symbolic constants
constexpr std::string_view s = "Hello, world!";
```

## Files in this Chapter
| File | What it demonstrates |
|------|----------------------|
| literals.cpp | C++ literals and their suffixes |
| strings.cpp | std::string usage and input handling |
| string_view.cpp | std::string_view usage and benefits |

## What to Remember
- Avoid passing `std::string` by value when unnecessary; prefer const references.
- Use `std::string_view` for read-only string access to avoid unnecessary copies.
- Prefer `std::string_view` for function parameters and return types involving string literals.