//prior to compilation, each code (.cpp) file goes through a preprocessing phase

/* When the preprocessor runs, it scans through the code file (from top to bottom), 
looking for preprocessor directives. Preprocessor directives (often just called directives) 
are instructions that start with a # symbol and end with a newline (NOT a semicolon). 


When you #include a file, the preprocessor replaces the #include directive with 
the contents of the included file. The included contents are then preprocessed 
(which may result in additional #includes being preprocessed recursively), 
then the rest of the file is preprocessed.

*/

#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}

/* When the preprocessor runs on this program, the preprocessor will replace 
#include <iostream> with the contents of the file named “iostream” and then 
preprocess the included content and the rest of the file. */