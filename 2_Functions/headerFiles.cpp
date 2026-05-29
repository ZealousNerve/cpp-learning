/* C++ code files (with a .cpp extension) are not the only files commonly seen in C++ programs. 
The other type of file is called a header file. Header files usually have a .h extension, 
but you will occasionally see them with a .hpp extension or no extension at all. */

//Header files allow us to put declarations in one place and then import them wherever we need them. 
//This can save a lot of typing in multi-file programs.


#include <iostream>
int main(){
    std::cout << "Hello, world!";
    return 0;
}

//std::cout has been forward declared in the “iostream” header file.

/* When you #include a file, the content of the included file is inserted at the point of inclusion. 
This provides a useful way to pull in declarations from another file. */


/* header files only consist of two parts:
    1.Header Guard
    2.The actual content of the header file
*/

/* Prefer a .h suffix when naming your header files (unless your project already follows some other convention).
This is a longstanding convention for C++ header files, and most IDEs still default to .h over other options. */

//If a header file is paired with a code file (e.g. add.h with add.cpp), they should both have the same base name (add).

//you should avoid putting function or variable definitions in header files

//Although the preprocessor will happily do so, you should generally not #include .cpp files.

/* Use double quotes to include header files that you’ve written or are expected to be found in the current directory.
Use angled brackets to include headers that come with your compiler, OS, or third-party libraries you’ve installed 
elsewhere on your system. */

//Use the standard library header files without the .h extension. User-defined headers should still use a .h extension.


//----------------------------------------------------------------------------------------------------------------------
//Including header files from other directories

/* One (bad) way to do this is to include a relative path to the header file you want to 
include as part of the #include line. For example: 

#include "headers/myHeader.h"
#include "../moreHeaders/myOtherHeader.h"

While this will compile (assuming the files exist in those relative directories), 
the downside of this approach is that it requires you to reflect your directory structure in your code. 
If you ever update your directory structure, your code won’t work anymore.


In your tasks.json configuration file, add a new line in the “Args” section:
"-I./source/includes",
There is no space after the -I. For a full path (rather than a relative path), remove the . after -I.

*/

//It’s common that the content of a header file will make use of something that is declared (or defined) in another header file
