읏

# 08_control_flow

Control flow structures enable programs to make decisions and repeat actions based on conditions and iterations.

────────────────────────────────────────────────────
## Key Concepts
- **Switch Statements** evaluate an expression and execute associated case blocks based on matching values.
- **Break Statements** exit a switch block or loop, preventing further execution of subsequent cases or iterations.
- **Fallthrough** allows execution to continue to the next case without a break, indicated by [[fallthrough]].
- **Integral Types** are required for switch conditions, including enums and convertible types.
- **Default Case** handles unmatched values in a switch statement.
- **Loop Control** uses break and continue to manage iteration flow.
- **Conditionals** use if-else to execute code based on boolean expressions.
- **Range-Based Loops** iterate over elements in containers like arrays and vectors.
- **Nested Loops** allow multiple loops to execute within each other.
- **Labelled Statements** enable jumping to specific points in code using goto.

────────────────────────────────────────────────────
## Critical Insights
### Why Use [[fallthrough]] in Switch Statements?
```cpp
case 2:
    std::cout << "Two";
    [[fallthrough]];
case 3:
    std::cout << "Three";
    break;
```
Using [[fallthrough]] explicitly indicates intentional fallthrough, avoiding compiler warnings and improving code clarity.

### What Happens If You Forget to Break in a Switch?
```cpp
case 1:
    std::cout << "One";
case 2:
    std::cout << "Two";
    break;
```
Forgetting to break causes fallthrough, leading to unintended execution of subsequent cases. This can result in logic errors and hard-to-debug behavior.

────────────────────────────────────────────────────
## What to Remember
⚠️ Always use break or return to exit switch cases and loops to prevent unintended fallthrough.  
⚠️ Ensure switch conditions are integral types or enums to avoid compilation errors.  
⚠️ Use [[fallthrough]] to indicate intentional fallthrough and avoid compiler warnings.