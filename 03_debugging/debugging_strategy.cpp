//Errors generally fall into one of two categories: syntax errors, and semantic errors (logic errors).

/*
one important step in debugging is to reproduce the problem or error, suppose I have a problem, but I told my
friend to debug it but as he runs, the code worked so how will he debug and for this we need to reproduce the error
again and again until we find the exact problem, suppose the problem is the code will not run on my device, suppose
my compiler is not working, so to know this, we need to reproduce the error again and again
*/

/*
 * debugging tactic #1:commenting out a part of code
   suppose an issue is there, and we comment some function based on our instinct if commenting that make the code run,
   then definitely that's the part where we are having the problem, if not resolved and issue still persists then the
   error is caused due to other function, or if some other error pops then maybe the code is dependent mainly on that
   commented function so we need to uncomment that

 * debugging tactic #2:validating our code flow
   sometimes in a program a function is called once or many times, now how do we know whether a function is called or not
   or which function is called at the time of issue, so that's why in our code at the start of every function we print
   a line like "inside main function" or "main function is called" so that we can check okay this part of code run
   but no error till now, ohh! this part of code run and the error is just after this step

   we use std::cerr instead of std::cout for this case, because std::cout is buffered means there could be some delay before
   printing, so maybe the error cause the code to crash and our buffer isn't printed yet so how do we know which part
   was causing the problem, and that's why we use std::cerr because it is unbuffered so it will use more resource but
   print immediately

 * debugging tactic#3:printing values
   similar to above we can print the values of variable at each step to check whether the variable are taking correct
   values or not, we will use std::cerr to print this


   all these print tactics are not good because it can clutter our code, and we may forget to remove or while removing,
   we remove an extra part so this will cause a problem

   we will use these methods to find a bug then after we are done with these print statement we will either remove then
   or comment them, again when we need them we need to find all debug statement and uncomment them or rewrite them again
   from scratch which will be very hectic, and that's why we will be using preprocessor directives to enable or disable
   those statements(shown below)

   #define DEBUG_ENABLE --comment this line to disable debug and debugging statements
   #ifdef DEBUG_ENABLE
   std::cerr << "the value of x: " << x;
   #endif


 */

/*
   or alternative method for above task is to use a logger, store everything in a timestamped log file, and it will
   reduce the clutter also

   C++ contains an output stream named std::clog that is intended to be used for writing logging information.
   However, by default, std::clog writes to the standard error stream (the same as std::cerr).
   And while you can redirect it to file instead, this is one area where you’re generally better off using one of the
   many existing third-party logging tools available. Which one you use is up to you.

   we’ll show what outputting to a logger looks like using the plog logger. Plog is implemented as a set of header files,
   so it’s easy to include anywhere you need it, and it’s lightweight and easy to use.

   the code of it is given below:
 */

/*
#include <plog/Log.h> // Step 1: include the logger headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>

int getUserInput(){
  PLOGD << "getUserInput() called"; // PLOGD is defined by the plog library
  std::cout << "Enter a number: ";
  int x{};
  std::cin >> x;
  return x;
}

int main(){
  plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger
  PLOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console
  int x{ getUserInput() };
  std::cout << "You entered: " << x << '\n';
  return 0;
}

  plog::init(plog::none, "Logfile.txt"); // used none to disable the logging
  */

//output--------
//2018-12-26 20:03:33.295 DEBUG [4752] [main@19] main() called
// 2018-12-26 20:03:33.296 DEBUG [4752] [getUserInput@7] getUserInput() called

//In larger or performance-sensitive projects, faster and more feature-rich loggers may be preferred, such as spdlog.


