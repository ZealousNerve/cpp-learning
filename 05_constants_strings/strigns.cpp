/*C-style string literals we have seen, but it is best to avoid it as there are many issues with c-style string variable

 and for this, c++ introduced two additional string types which is std::string and std::string_view
 */

//STD::STRING;

#include <iostream>
#include <string> // allows use of std::string
int main(){
    std::string name {"Alex"};
    name = "John";
    std::cout << "My name is: " << name << '\n';

    std::string myID{ "45" }; // "45" is not the same as integer 45!
    //In string form, numbers are treated as text, not as numbers, and thus they can not be manipulated as numbers


    //now the point is how can we take input into strings, if we take using std::cin then as the first whitespace will
    //be encountered, it will stop at that point, and to resolve this we use, std::getline();


    std::getline(std::cin >> std::ws, name);

    /*now what is std::ws, as we studied before that there are output manipulators like std::setprecision(), there are
    input manipulator also like std::ws, it tells the std::cin to ignore any leading whitespace before extraction
    leading whitespace means any kind of whitespace which is at the start of the string*/

    /*as we know, that whenever we enter anything in cin, it takes a new line character also, so suppose the first input
    ask a number then we write 2 so it will be stored as 2\n in buffer, and in second output, before we could enter
    anything it will take the remaining \n and move to next step, and we couldn't even write anything, and that's why
    we are using std::ws to remove these types of whitespaces(leading)*/

    //This needs to be done for each std::getline() call, as std::ws is not preserved across calls.

    //and this std::string won't take a \n as input at the end of string as we have seen in c-type string literal

    /*Also note that std::string::length() returns an unsigned integral value (most likely of type size_t).
    If you want to assign the length to an int variable, you should static_cast it to avoid compiler warnings
    about signed/unsigned conversions:
    */

    int length { static_cast<int>(name.length()) };
    std::cout << length << '\n';

    //Do not pass std::string by value, as it makes an expensive copy.


    /*Double-quoted string literals (like “Hello, world!”) are C-style strings by default (and thus, have a strange type).
    We can create string literals with type std::string by using a s suffix after the double-quoted string literal.
    The s must be lower case.*/

    using namespace std::string_literals; // easy access to the s suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal

    return 0;

}