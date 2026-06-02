# Formatting Output in C++ — `<iomanip>` & `<iostream>`

## Headers Used
```cpp
#include <iostream>   // for std::cout
#include <iomanip>    // for std::setw
#include <climits>    // for CHAR_BIT (number of bits in a byte)
```

---

## Key Concepts

### 1. `CHAR_BIT`
- Defined in `<climits>`
- Gives the number of bits in a single byte (almost always `8`)
```cpp
std::cout << "A byte is " << CHAR_BIT << " bits\n";
// Output: A byte is 8 bits
```

---

### 2. `std::left` — Left Justify Output
- A **sticky manipulator** (stays active for all subsequent output)
- Aligns text to the **left** within the column width
```cpp
std::cout << std::left;  // all following output is left-aligned
```

---

### 3. `std::setw(n)` — Set Column Width
- Defined in `<iomanip>`
- Sets the **minimum width** for the **next single output only** (not sticky)
- Pads with spaces if the output is shorter than `n`
```cpp
std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
// Output: "bool:           1 bytes"
//          |<--- 16 chars -->|
```

---

### 4. `sizeof()` — Get Size of a Type
- Returns size in **bytes** of a type or variable
- Evaluated at **compile time**
```cpp
sizeof(int)         // typically 4
sizeof(long long)   // typically 8
sizeof(long double) // typically 8, 12, or 16
```

---

## Full Example Explained
```cpp
std::cout << std::left;                          // left-align everything
std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
//                   ^             ^          ^
//             column width    label      actual size
```

**Output on a typical 64-bit system:**
```
A byte is 8 bits

bool:           1 bytes
char:           1 bytes
short:          2 bytes
int:            4 bytes
long:           8 bytes
long long:      8 bytes
float:          4 bytes
double:         8 bytes
long double:    16 bytes
```

---

## Quick Reference Table

| Manipulator / Tool | Header     | Sticky? | Purpose                        |
|--------------------|------------|---------|--------------------------------|
| `std::left`        | `<iostream>` | ✅ Yes  | Left-align output              |
| `std::right`       | `<iostream>` | ✅ Yes  | Right-align output (default)   |
| `std::setw(n)`     | `<iomanip>`  | ❌ No   | Set width for next output only |
| `sizeof(type)`     | built-in   | —       | Get byte size of a type        |
| `CHAR_BIT`         | `<climits>`  | —       | Number of bits in a byte       |