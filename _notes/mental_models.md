

# Special Comment Tags


> TODO  - Work that still needs to be done.
// TODO: Implement this function

>FIXME - Known bug or issue that needs fixing.
// FIXME: Possible bug here

>NOTE  - Important information or reminder.
// NOTE: Important detail

### These are regular comments, but many IDEs highlight them to make them easier to find.


---

### If you want to match any letter case, you can use the following function to convert the user’s input to lower case:



````
#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower
#include <iterator>  // for std::back_inserter
#include <string>
#include <string_view>

// This function returns a std::string that is the lower-case version of the std::string_view passed in.
// Only 1:1 character mapping can be performed by this function
    
std::string toASCIILowerCase(std::string_view sv)
{
     std::string lower{};
     std::transform(sv.begin(), sv.end(), std::back_inserter(lower),
        [](char c)
        {
            return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        });
    return lower;
}
````

---

### This function steps through each character in std::string_view sv, converts it to a lower case character using std::tolower() (with the help of a lambda), and then appends that lower-case character to lower.