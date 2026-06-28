//Don’t forget to end your type definitions with a semicolon.

//Name your program-defined types starting with a capital letter and do not use a suffix.

/*A program-defined type used in only one code file should be defined in that code
file as close to the first point of use as possible.*/

/*A program-defined type used in multiple code files should be defined in a header file
with the same name as the program-defined type and then #included into each code file as needed.*/

//types are partially exempt from the one-definition rule: a given type is allowed to be defined in multiple code files.

/*First, you can still only have one type definition per code file (this usually isn’t a problem since header
guards will prevent this). Second, all of the type definitions for a given type must be identical, otherwise
undefined behavior will result.*/