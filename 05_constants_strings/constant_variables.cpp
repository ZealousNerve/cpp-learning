//constant variables are those variables which doesn't change after it is defined that too during initialization only

const double gravity { 9.8 };  // preferred use of const before type
int const sidesInSquare { 4 }; // "east const" style, okay but not preferred

// in C++ is use intercapped names with a ‘k’ prefix to name a constant(e.g. kEarthGravity).

/*
because const variables act like normal variables (except they can not be assigned to), there is no reason that
they need a special naming convention. For this reason, we prefer using the same naming convention that we use for
non-const variables (e.g. earthGravity).

Function parameters can be made constants via the const keyword:
in modern C++ we don’t make value parameters const because we generally don’t care if the function changes the value
of the parameter (since it’s just a copy that will be destroyed at the end of the function anyway).

Prefer constant variables over object-like macros with substitution text.
*/


