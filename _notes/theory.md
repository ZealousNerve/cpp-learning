# Theory Notes, Cross-Chapter Insights

> Things that don't belong to one chapter. The meta-knowledge of C++.
> Every entry here was earned by noticing something, not just reading it.

---

## Compiler Behavior

### Error locations can lie
The compiler sometimes reports an error on the line *after* the actual problem.
If the flagged line looks fine, check the line above it.

```cpp
int x = 5     // ← missing semicolon, compiler reports error on NEXT line
int y = 10;   // ← compiler says error is HERE
```

### Compilation is per-file
C++ compiles each `.cpp` file in isolation. The compiler has no knowledge
of other `.cpp` files during compilation. This is why:
- Forward declarations and header files exist
- You can't just call a function defined in another file without declaring it first
- The *linker* (a separate step) connects everything

---

## Naming Conventions

### snake_case vs camelCase
Both are valid. Pick one per project and never mix them.

```cpp
int player_health;   // snake_case, common in C standard library style
int playerHealth;    // camelCase, common in OOP/Java style

// In C++, the standard library uses snake_case:
std::string my_string;
std::vector<int> item_list;
```

### What NOT to name things
- Don't start identifiers with `_`, reserved for compiler/standard library use
- Don't use all-caps except for macros (and even then, prefer `constexpr`)
- Don't use single letters except for loop counters and template parameters

---

## Preprocessor Directives

### Always on their own line
```cpp
// CORRECT
#include <iostream>
#include <string>

// WRONG
#include <iostream> #include <string>  // won't compile
```

### They are not C++
The preprocessor runs before the compiler. `#define`, `#include`, `#ifdef` are
text-substitution instructions, not C++ code. They have no semicolons.
They don't understand types. They don't respect scope.

---

## Operators

### Long lines: break at the operator, put it at the START of the next line
```cpp
// CORRECT, operator leads the continuation line
std::cout << 3 + 4
    + 5 + 6
    * 7 * 8;

// AVOID, operator at end makes it easy to miss
std::cout << 3 + 4 +
    5 + 6 *
    7 * 8;
```

### Operator chaining via return value
`operator=` and `operator<<` both return their left operand.
That's why chaining works:

```cpp
x = y = z = 5;              // assigns 5 to z, returns z, assigns to y, etc.
std::cout << a << b << c;   // outputs a, returns cout, outputs b, etc.
```

---

## Literals vs Variables, The Memory Distinction

```
Literal → value baked directly into the executable binary
Variable → value stored in memory, can change at runtime
```

A literal `42` in your code becomes bytes in the `.text` section of the compiled binary.
A variable `int x` becomes a location in the stack frame at runtime.
This is why literals are "compile-time constants" and variables are "runtime values."

---

## Types of Operators (by operand count)

| Type | Operands | Example |
|------|----------|---------|
| Unary | 1 | `-x`, `!flag`, `++i` |
| Binary | 2 | `a + b`, `x == y` |
| Ternary | 3 | `condition ? a : b` |
| Nullary | 0 | `throw` (in some contexts) |

---

## Multi-line Comments, The One Rule

Never nest multi-line comments inside multi-line comments.
But nesting single-line comments inside multi-line is fine.

```cpp
/* This is fine:
   // single-line comment inside
   // another one
*/

/* This BREAKS:
   /* nested multi-line, the first */ ends here, rest is code */
```

---
## Extras:
This process of making structural changes to your code without changing its behavior is called refactoring. 
The goal of refactoring is to make your program less complex by increasing its organization and modularity.

So how long is too long for a function? A function that takes up one vertical screen worth of code is generally 
regarded as too long -- if you have to scroll to read the whole function, the function’s comprehensibility drops significantly. 
Ideally, a function should be less than ten lines. Functions that are less than five lines are even better.

---
std::cout << "The value of x is: " << x << '\n'; // standalone \n goes in single quotes <br>
std::cout << "First line\nSecond line\n";        // \n can be embedded in double quotes


---
Whenever you see C++ syntax (excluding the preprocessor) that makes use of angled brackets (<>), 
the thing between the angled brackets will most likely be a type. This is typically how C++ deals with code 
that need a parameterized type.
---

With normal functions, we call function(object). With member functions, we call object.function().

---
blocks are treated as a single statement
````
*Add to this file whenever something clicks that belongs to no single chapter.*
