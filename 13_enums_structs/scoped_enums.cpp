/*Scoped enumerations work similarly to unscoped enumerations ( Unscoped enumerations), but have two primary
differences: They won’t implicitly convert to integers, and the enumerators are only placed into the scope region
of the enumeration (not into the scope region where the enumeration is defined). means no need of a namespace here

To make a scoped enumeration, we use the keywords enum class. The rest of the scoped enumeration definition is
the same as an unscoped enumeration definition

scoped enumerations use the class keyword, they aren’t considered to be a “class type” (which is reserved
for structs, classes, and unions).*/

#include <iostream>
#include <utility> // for std::to_underlying() (C++23)
#include <type_traits> // for std::underlying_type_t

// Overload the unary + operator to convert an enum to the underlying type
// adapted from https://stackoverflow.com/a/42198760, thanks to Pixelchemist for the idea
// In C++23, you can #include <utility> and return std::to_underlying(a) instead
template <typename T>
constexpr auto operator+(T a) noexcept
{
    return static_cast<std::underlying_type_t<T>>(a);
}



int main(){
    enum class Color{ // "enum class" defines this as a scoped enumeration rather than an unscoped enumeration
        red, // red is considered part of Color's scope region
        blue,
    };

    enum class Fruit{
        banana, // banana is considered part of Fruit's scope region
        apple,
    };

    Color color { Color::red }; // note: red is not directly accessible, we have to use Color::red
    Fruit fruit { Fruit::banana }; // note: banana is not directly accessible, we have to use Fruit::banana

    if (color == fruit) // compile error: the compiler doesn't know how to compare different types Color and Fruit
        std::cout << "color and fruit are equal\n";
    else
        std::cout << "color and fruit are not equal\n";

//---------------------------------------------------------------------------------------------------------------------

    Color shirt { Color::red };

    if (shirt == Color::red) // this Color to Color comparison is okay
        std::cout << "The shirt is red!\n";
    else if (shirt == Color::blue)
        std::cout << "The shirt is blue!\n";

//---------------------------------------------------------------------------------------------------------------------

    Color color1 { Color::blue };

    std::cout << color1 << '\n'; // won't work, because there's no implicit conversion to int
    std::cout << static_cast<int>(color1) << '\n';   // explicit conversion to int, will print 1
    std::cout << std::to_underlying(color1) << '\n'; // convert to underlying type, will print 1 (C++23)

//----------------------------------------------------------------------------------------------------------------------

    Color color2{ static_cast<Color>(1) }; // static_cast our integer to a Pet

    /*can list initialize a scoped enumeration using an integral value without the static_cast (and unlike an
    unscoped enumeration, you don’t need to specify a base):*/

    Color color3 { 1 }; // okay

//----------------------------------------------------------------------------------------------------------------------

    std::cout << +Color::blue << '\n'; // convert Animals::elephant to an integer using unary operator+ (see the start
    //of the code

//----------------------------------------------------------------------------------------------------------------------

    //Introduced in C++20, a using enum statement imports all of the enumerators from an enum into the current scope.
    //When used with an enum class type, this allows us to access the enum class enumerators without having to prefix
    //each with the name of the enum class.

    using enum Color; // bring all Color enumerators into current scope (C++20)
    // We can now access the enumerators of Color without using a Color:: prefix


    return 0;
}

