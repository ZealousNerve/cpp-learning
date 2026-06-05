/*If two identical identifiers are introduced into the same program in a way that the compiler or linker can’t tell
them apart, the compiler or linker will produce an error. This error is generally referred to as a
naming collision (or naming conflict).

If the colliding identifiers are introduced into the same file, the result will be a compiler error. If the colliding
identifiers are introduced into separate files belonging to the same program, the result will be a linker error.

A scope region is an area of source code where all declared identifiers are considered distinct from names declared in
other scopes (much like the cities in our analogy). Two identifiers with the same name can be declared in separate scope
regions without causing a naming conflict. However, within a given scope region, all identifiers must be unique,
otherwise a naming collision will result.*/

//NAMESPACE:

/*A name declared within a scope region (such as a namespace) is distinct from any identical name declared in another scope.
A namespace may only contain declarations and definitions. Executable statements are only allowed as part of a definition
(e.g. of a function).

Namespaces are often used to group related identifiers in a large project to help ensure they don’t inadvertently
collide with other identifiers. For example, if you put all your math functions in a namespace named math,
then your math functions won’t collide with identically named functions outside the math namespace.

In C++, any name that is not defined inside a class, function, or a namespace is considered to be part of an
implicitly-defined namespace called the global namespace (sometimes also called the global scope).


When you use an identifier that is defined inside a non-global namespace (e.g. the std namespace), you need to tell
the compiler that the identifier lives inside the namespace.*/

#include <iostream>
int main(){
    std::cout << "Hello world!"; // when we say cout, we mean the cout defined in the std namespace
    return 0;
}

/*The :: symbol is an operator called the scope resolution operator. The identifier to the left of the :: symbol
identifies the namespace that the name to the right of the :: symbol is contained within.

Another way to access identifiers inside a namespace is to use a using-directive statement.*/

#include <iostream>

using namespace std; // this is a using-directive that allows us to access names in the std namespace with no namespace prefix
int main(){
    cout << "Hello world!";
    return 0;
}

/*Avoid using-directives (such as using namespace std;) at the top of your program or in header files.
They violate the reason why namespaces were added in the first place.*/