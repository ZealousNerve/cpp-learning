//we can define our own namespace, the syntax is as follows:
namespace NamespaceIdentifier
{
    // content of namespace here
}

/*A namespace must be defined either in the global scope, or inside another namespace. we can call it using the scope
resolution operator, e.g. NamespaceIdentifier::func(), and in same way ::func() will look in global namespace*/



#include <iostream>
void print(){ // this print() lives in the global namespace
    std::cout << " there\n";
}

namespace Foo{
    void print(){ // this print() lives in the Foo namespace
        std::cout << "Hello";
    }

    void printHelloThere(){
        print();   // calls print() in Foo namespace,

        /*If an identifier inside a namespace is used and no scope resolution is provided, the compiler will first try to
        find a matching declaration in that same namespace. If no matching identifier is found, the compiler will then
        check each containing namespace in sequence to see if a match is found, with the global namespace being checked last.*/

        ::print(); // calls print() in global namespace
    }
}

/*same as we declared functions in header files, we can declare namespace also, and then apply header guards and
define that function inside namespace later in the main.cpp, the syntax of declaring namespace in header file
is shown below:*/

//--------------------------add.h----------------------------
#ifndef ADD_H
#define ADD_H
namespace BasicMath{
    // function add() is part of namespace BasicMath
    int add(int x, int y);
}
#endif
//------------------------------------------------------------


/*It’s legal to declare namespace blocks in multiple locations (either across multiple files, or multiple places within
the same file). All declarations within the namespace are considered part of the namespace. for e.g. there can be
multiple namespaces of same name, and content can be different, all will be same namespace just different parts*/

/*namespace can be nested and to call we keep on adding more and more scope resolution operator like ns1::ns2::func()
one way to do so is using simple nesting, other way of doing is given below*/

namespace ns1::ns2 { int func(){return 0;} }
namespace ns1 { void func1(){} }

int main(){
    Foo::printHelloThere();

    /*Because typing the qualified name of a variable or function inside a nested namespace can be painful, C++ allows
    you to create namespace aliases, which allow us to temporarily shorten a long sequence of namespaces into
    something shorter:*/

    namespace Active = ns1::ns2; // active now refers to ns1::ns2
    std::cout << Active::func() << '\n';

    return 0;
}