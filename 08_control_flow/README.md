nonce

# Control Flow and Randomization

## Key Concepts
- **Switch Statements**: Used for branching based on integral or enum values. Each case must be a constant expression.
- **Fallthrough**: Default behavior in C++ is to not fall through cases unless explicitly stated. Use `[[fallthrough]]` for intentional fallthrough.
- **Random Number Generation**: Use `<random>` header for robust random number generation. `std::mt19937` is a high-quality PRNG.
- **Seeding**: Properly seed PRNGs with `std::random_device` for better randomness. Avoid reseeding.
- **Control Flow**: `break`, `continue`, and `return` control the flow of execution. `switch` requires `break` (or `return`, `throw`, etc.) to exit the block.
- **Initialization in Switch**: Variables can be declared in switch blocks, but care must be taken with initialization and scope.

## Critical Insights
### ❌ Bad: Reseeding PRNG in a function
```cpp
int getCard_BAD()
{
    std::mt19937 mt{ std::random_device{}() }; // re-seeded every call → bad quality + slow
    std::uniform_int_distribution card{ 1, 52 };
    return card(mt);
}
```

### ✅ Good: Single PRNG instance
```cpp
int getCard_GOOD()
{
    static std::mt19937 mt{ std::random_device{}() }; // initialized only once
    std::uniform_int_distribution card{ 1, 52 };
    return card(mt);
}
```

### ❌ Bad: Initialization in switch case
```cpp
case 2:
    int y = 5; // illegal: initialization is not allowed if subsequent cases exist
```

## Files in this Chapter
| File | What it demonstrates |
|------|----------------------|
| switch.cpp | Switch statements, fallthrough, and variable scope |
| random.cpp | Random number generation with std::mt19937 and distributions |
| control_flow.cpp | Control flow with break, continue, and return |
| seeding.cpp | Proper seeding of PRNGs with std::random_device |
| switch_init.cpp | Variable initialization within switch cases |

## What to Remember
- Always use `[[fallthrough]]` for intentional fallthrough in switch statements.
- Avoid reseeding PRNGs unless necessary; seed once and reuse.
- Be cautious with variable initialization in switch cases; avoid initializing if subsequent cases exist.