𝖋

# 11_templates

This chapter explores templates in C++, focusing on function templates, non-type parameters, and type deduction.

## Key Concepts
- **Function Templates**: Generic functions that can work with any data type, deducing types at compile time.
- **Non-Type Template Parameters**: Allow functions to accept fixed values like integers or characters as parameters.
- **Type Deduction**: The compiler automatically determines the type of arguments passed to a function template.
- **Static Assertions**: Used to enforce compile-time conditions, preventing invalid code from compiling.
- **Template Specialization**: Allows defining specific implementations for particular types or values.
- **Static Variables in Templates**: Each template instantiation has its own static variable, enabling per-type state.
- **Integral Promotion**: Converts smaller integer types to larger ones, like char to int.
- **Template Overloading**: Multiple templates can be defined for the same function name, distinguished by parameters.
- **Template Guards**: Prevent unintended template instantiations by using `= delete`.
- **Template Metaprogramming**: Enables compile-time computation and code generation through templates.

## Critical Insights
### Why Type Deduction Fails with Mixed Types
```cpp
template<typename T> T max(T a, T b) { return a > b ? a : b; }
```
Type deduction fails when passing different types (e.g., `max(3, 3.5)`), requiring explicit type specification or using `std::common_type`.

### How Non-Type Parameters Work
```cpp
template<int N> void printN() { std::cout << N << '\n'; }
```
Non-type parameters like `N` are fixed at compile time, allowing functions to operate on constant values directly.

## What to Remember
⚠️ ⚠️ ⚠️  
⚠️ Always specify types explicitly when mixing different data types in templates.  
⚠️ Non-type parameters are compile-time constants and cannot be modified at runtime.  
⚠️ Use static assertions to catch errors early and prevent invalid template instantiations.