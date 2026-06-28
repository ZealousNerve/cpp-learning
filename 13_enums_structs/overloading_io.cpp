#include <iostream>
#include <limits>       // std::numeric_limits (for ignore())
#include <optional>     // std::optional<T>
#include <string>       // std::string (for getline/input buffer)
#include <string_view>  // std::string_view (lightweight, no heap alloc)

/*Basic operator overloading is fairly straightforward:

1. Define a function using the name of the operator as the function’s name.
2. Add a parameter of the appropriate type for each operand (in left-to-right order). One of these parameters
   must be a user-defined type (a class type or an enumerated type), otherwise the compiler will error.
3. Set the return type to whatever type makes sense.
4. Use a return statement to return the result of the operation.*/

//to output an enumerator with its string value:


// ============================================================
// SECTION 1 — Pet enum + helpers (demonstrates operator>>)
// ============================================================

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

// NOTE: constexpr + string_view = zero runtime cost name lookup.
// No dynamic allocation, no string copy — ideal for switch-based name maps.
constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

// NOTE: std::optional<Pet> is the clean way to express "might not find a match."
// Returning {} means std::nullopt — no value. Avoids sentinel values like -1.
constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;
    return {};
}

// pet is an in/out parameter
// NOTE: operator>> must return std::istream& so chaining (cin >> a >> b) works.
// The Pet& parameter is modified directly — this is the "out" part of in/out.
std::istream& operator>>(std::istream& in, Pet& pet)
{
    std::string s{};
    in >> s; // get input string from user

    std::optional<Pet> match { getPetFromString(s) };

    if (match) // if we found a match
    {
        pet = *match; // dereference std::optional to get matching enumerator
        return in;
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // NOTE: Setting failbit makes std::cin evaluate to false in boolean context.
    // This is what allows `if (std::cin)` to detect extraction failure cleanly.

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // pet = {};

    return in;
}

// ============================================================
// SECTION 2 — Color enum + helpers (demonstrates operator<<)
// ============================================================

enum Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout, std::cerr, etc...
// The return type and parameter type are references (to prevent copies from being made)
// NOTE: Color is passed by value (not reference) — enums are cheap to copy,
// and passing by value avoids accidental modification.
std::ostream& operator<<(std::ostream& out, Color color)
{
    out << getColorName(color); // print our color's name to whatever output stream out
    return out;                 // operator<< conventionally returns its left operand

    // The above can be condensed to the following single line:
    // return out << getColorName(color)
}

// ============================================================
// SECTION 3 — main() — tests both operators
// ============================================================

int main()
{
    // --- Test operator<< (Color output) ---
    Color shirt{ blue };
    std::cout << "Your shirt is " << shirt << '\n'; // it works!

    // --- Test operator>> (Pet input) ---
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    Pet pet{};
    std::cin >> pet;

    if (std::cin) // if we found a match
        std::cout << "You chose: " << getPetName(pet) << '\n';
    else
    {
        // NOTE: After a failbit, always clear() before ignore().
        // clear() resets the error flags so the stream is usable again.
        // ignore() flushes the bad input sitting in the buffer —
        // without it, the bad characters stay and break the next extraction.
        std::cin.clear(); // reset the input stream to good
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Your pet was not valid\n";
    }

    return 0;
}

// ============================================================
// PATTERN SUMMARY:
// operator<<(ostream&, EnumType)  → for OUTPUT  (printing enums)
// operator>>(istream&, EnumType&) → for INPUT   (reading enums, ref param)
// Both return their stream parameter to allow chaining.
// Use std::optional<T> for safe "found or not found" returns — no sentinel values.
// Use failbit to signal invalid input; always clear() + ignore() to recover.
// ============================================================