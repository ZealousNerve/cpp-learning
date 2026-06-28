//Consider the following academic example:

//(we are defining a function in header file just for the understanding, this is not recommended at all)

// square.h:----------------
int getSquareSides(){
    return 4;
}

//wave.h:--------------------
//     #include "square.h"


//main.cpp--------------------
//    #include "square.h"
//    #include "wave.h"

int main(){
    return 0;
}

//here the main.cpp in including square.h which contains the function definition, then includes wave.h which itself
//includes square.h so in simple terms the function definition is copied in main.cpp twice which will cause the ODR violation


//and that's why header guards(also called as include guards) are used to resolve conflict in such issues


//update square.h header file with header guard

// square.h:---------------

#ifndef SQUARE_H
#define SQUARE_H
//    int getSquareSides(){
//        return 4;
//    }
#endif

//so all the header files must contain this header guards, as you can see the ifdef directives check whether that square.h
//is defined earlier, if yes then do nothing if not defined then add that definition

/*
remember these preprocessors are just copy and paste replacement thing, so now if square.h is imported then the main.cpp will
contain that square.h and that ifndef directive will run and define the function as it wasn't defined earlier,
then when main.cpp includes wave.h then, then square.h in wave.h already sees that it is defined in main.cpp so it won't let
it get defined again
*/


//by convention is set to the full filename of the header file, typed in all caps, using underscores for spaces or punctuation.
//For example, square.h would have the header guard: SQUARE_H

//Because of this possibility for guard name conflicts, many developers recommend using a more complex/unique name in your
// header guards. Some good suggestions are a naming convention of PROJECT_PATH_FILE_H, FILE_LARGE-RANDOM-NUMBER_H,
// or FILE_CREATION-DATE_H.



// Modern compilers support a simpler, alternate form of header guards using the #pragma preprocessor directive:

/*With traditional header guards, the developer is responsible for guarding the header (by using preprocessor directives
#ifndef, #define, and #endif). With #pragma once, we’re requesting that the compiler guard the header.*/


#pragma once
// your code here