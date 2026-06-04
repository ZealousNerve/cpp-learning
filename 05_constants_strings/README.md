# String and String View in C++

## Key Concepts

- **`std::string`** is used for storing and modifying text, handling user input, and returning values from functions.
- **`std::string_view`** is a non-owning, read-only view of a string, ideal for function parameters and avoiding unnecessary copies.
- **Literal suffixes** (`s`, `sv`) allow for easy creation of `std::string` and `std::string_view` from string literals.
- **`std::string_view`** must never outlive the string it views, as it does not take ownership.
- **`std::string_view`** can be constructed from various sources: C-style strings, `std::string`, and string literals.
- **`std::string_view`** is preferred for function parameters when only read access is needed.

## Critical Insights

### ❌ Dangling `std::string_view` is undefined behavior
```cpp
{
    std::string temp { "I am temporary" };
    std::string_view watching { temp };
    std::cout << watching << '\n';   // ✅ fine — temp is alive here
}
// std::cout << watching;            // ❌ temp is gone → watching is dangling → UB
```

### ✅ Use `std::getline(std::cin >> std::ws, str)` for line input
```cpp
std::string str;
std::getline(std::cin >> std::ws, str);
```

### ✅ Prefer `std::string_view` for function parameters
```cpp
void printByView(const std::string_view& sv);
printByView("literal");    // ✅
printByView(owned);        // ✅
printByView(sv);           // ✅
```

## Files in this Chapter

| File | What it demonstrates |
|------|----------------------|
| `strings.cpp` | Demonstrates `std::string`, `std::string_view`, literal suffixes, and common usage patterns |

## What to Remember

- Never pass `std::string` by value unless you need a copy.
- Always use `std::getline(std::cin >> std::ws, str)` for line input.
- `std::string_view` must never outlive the string it views.