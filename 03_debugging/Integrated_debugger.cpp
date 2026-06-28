//To ensure that all output from std::cout is output immediately, you can temporarily add the following statement to the
//top of your main() function:

#include <iostream>
int main() {
  std::cout << std::unitbuf; // enable automatic flushing for std::cout (for debugging)
  std::cout << "Hello";
  std::cout << "World!";
}
/*
  The step into command executes the next statement in the normal execution path of the program, and then pauses
  execution of the program so we can examine the program’s state using the debugger. If the statement being executed
  contains a function call, step into causes the program to jump to the top of the function being called, where it will pause.

  Like step into, The step over command executes the next statement in the normal execution path of the program. However,
  whereas step into will enter function calls and execute them line by line, step over will execute an entire function
  without stopping and return control to you after the function has been executed.

  Unlike the other two stepping commands, Step out does not just execute the next line of code. Instead, it executes all
  remaining code in the function currently being executed, and then returns control to you when the function has returned.


  If you step past your intended destination, the usual thing to do is stop debugging and restart debugging again, being
  a little more careful not to pass your target this time.

  The first useful command is commonly called Run to cursor. This Run to cursor command executes the program until
  execution reaches the statement selected by your cursor. Then it returns control to you so you can debug starting at
  that point. This makes for an efficient way to start debugging at a particular point in your code, or if already debugging,
  to move straight to some place you want to examine further.

  Once you’re in the middle of a debugging session, you may want to just run the program from that point forward.
  The easiest way to do this is to use the continue command. The continue debug command simply continues running the
  program as per normal, either until the program terminates, or until something triggers control to return back to
  you again (such as a breakpoint).

  The continue command has a twin brother named start. The start command performs the same action as continue,
  just starting from the beginning of the program. It can only be invoked when not already in a debug session.

  A breakpoint is a special marker that tells the debugger to stop execution of the program at the breakpoint
  when running in debug mode.

  Breakpoints have a couple of advantages over run to cursor. First, a breakpoint will cause the debugger to return
  control to you every time they are encountered (unlike run to cursor, which only runs to the cursor once each time
  it is invoked). Second, you can set a breakpoint and it will persist until you remove it, whereas with run to cursor
  you have to locate the spot you want to run to each time you invoke the command.

  all modern integrated debuggers provide another feature, called a watch window. The watch window is a window where
  you can add variables you would like to continually inspect, and these variables will be updated as you step through your program.

  Some debuggers will allow you to set a breakpoint on a watched variable rather than a line. This will cause the
  program to stop execution whenever the value of that variable changes.

  The call stack is a list of all the active functions that have been called to get to the current point of execution.
  The call stack includes an entry for each function called, as well as which line of code will be returned to when the
  function returns. Whenever a new function is called, that function is added to the top of the call stack.
  When the current function returns to the caller, it is removed from the top of the call stack, and control returns
  to the function just below it.


*/