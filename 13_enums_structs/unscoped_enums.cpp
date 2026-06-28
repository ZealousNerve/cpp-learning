#include<iostream>
#include <cstdint>  // for std::int8_t
#include <optional> // for std::optional

/*
1. An enumeration (also called an enumerated type or an enum) is a compound data type whose values are
   restricted to a set of named symbolic constants (called enumerators).

2. each enumeration needs to be fully defined before we can use it (a forward declaration is not sufficient).

3. There are two types of enums, unscoped and scoped enumerations*/

//TODO: ================================================================================================
//                                 UNSCOPED ENUMS:
//TODO: ================================================================================================

// Define a new unscoped enumeration named Color
//Enumerations don’t have to be named, but unnamed enumerations should be avoided in modern C++.

enum Color
{
   // Here are the enumerators
   // These symbolic constants define all the possible values this type can hold
   // Each enumerator is separated by a comma, not a semicolon
   //Enumerators are implicitly constexpr.
   //Name your enumerated types starting with a capital letter. Name your enumerators starting with a lower case letter.
   red,
   green, black, //can be written on same line also
   blue,    // trailing comma optional but recommended
}; // the enum definition must end with a semicolon


/*to reduce the chances of naming collision in same scope, we can name the enumerators with a prefix of enum name
   color_red, color_blue, color_green, or another way to avoid is to add the enum inside a namespace, which have its
   own scope: (shown below)

   Classes also provide a scope region, and it’s common to put enumerated types related to a class inside the
   scope region of the class.*/

namespace Color1{ // The names Color, red, blue, and green are defined inside namespace Color
    enum Color{
           red,
           green,
           blue,
    };
}

/*
   The specific integral type used to represent the value of enumerators is called the enumeration’s
   underlying type (or base).

   For unscoped enumerations, the C++ standard does not specify which specific integral type should be used as
   the underlying type, so the choice is implementation-defined.
*/

// Use an 8-bit integer as the enum underlying type
enum Animal : std::int8_t{
   /*each enumerator is automatically associated with an integer value based on its position in the enumerator list,
   the first enumerator is given the integral value 0, and each subsequent enumerator has a value one greater than
   the previous enumerator

   It is possible to explicitly define the value of enumerators. These integral values can be positive or negative,
   and can share the same value as other enumerators. Any non-defined enumerators are given a value one greater
   than the previous enumerator.*/

   cat = -3,    // values can be negative
   dog,         // -2
   pig,         // -1
   //no enumerator have the value 0, but still we can initialize an object with enum type with zero
   horse = 5,
   giraffe = 5, // shares same value as horse
   chicken,     // 6

   /*and unscoped enums can be implicitly converted to integers, so when we call std::cout << pig, it prints -1, not "pig"
   but the reverse is not implicit, one way of doing the reverse is to static cast, but we have to take care about
   the range of underlying type of enum.*/

   /*Make the enumerator representing 0 the one that is the best default meaning for your enumeration. If no good
   default meaning exists, consider adding an “invalid” or “unknown” enumerator that has value 0, so that state
   is explicitly documented and can be explicitly handled where appropriate.*/
};


int main()
{
   // Define a few variables of enumerated type Color
   Color apple { red };   // my apple is red
   Color shirt { green }; // my shirt is green
   Color bag { Color::black }; // also okay, accessing enumerator from scope of Color using scope resolution
   Color cup { blue };    // my cup is blue

   //TODO:   Color socks { white }; // error: white is not an enumerator of Color
   //TODO:   Color hat { 2 };       // error: 2 is not an enumerator of Color

   //enumerations are small and inexpensive to copy, it is fine to pass (and return) them by value.

   /*it is named unscoped because enumerators scope is same as enumeration scope, here, enumeration is defined in
   global namespace, so red is also in global namespace*/

   //an enumerator name can’t be used in multiple enumerations within the same scope


   /*Specify the base type of enumeration only when necessary.
   Warning Because std::int8_t and std::uint8_t are usually type aliases for char types, using either of
   these types as the enum base will most likely cause the enumerators to print as char values rather than int values.*/

   /*as we know the normal std::cout << enumeratorName will not print the name it will print the integral value, but
   if we want to print the string enum name, there are few ways, one way is altering std::cout, which is in next notes,
   or we can use an array, or a different function which will contain a switch case, so that we will pass the name of
   enums so the implicitly converted to  integral value will be passed to the function and based on that integral value
   the std::string_view will do its work*/

   return 0;
}

//this method shown below is same as we did a jugaad for std::cout, we did this for std::cin
constexpr std::optional<Color> getPetFromString(std::string_view sv)
{
   // We can only switch on an integral value (or enum), not a string
   // so we have to use if-statements here
   if (sv == "red")   return red;
   if (sv == "green")   return green;
   if (sv == "black")   return black;
   if (sv == "blue") return blue;
   
   return {};
}
