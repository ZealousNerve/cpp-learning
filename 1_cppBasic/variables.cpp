//5 common ways of initialization

int a;        // default-initialization (no initializer)

// Traditional initialization forms:
int b = 5;    // copy-initialization (initial value after equals sign)
int c (6);    // direct-initialization (initial value in parenthesis)

// Modern initialization forms (preferred):
int d {7};    // direct-list-initialization (initial value in braces)
int e {};     // value-initialization (empty braces)- initialize to zero


//As of C++17, copy-initialization, direct-initialization, and direct-list-initialization 
//behave identically in most cases. We’ll cover the most relevant case where they differ below.



//Copy-initialization is also used whenever values are implicitly copied, such as when passing 
//arguments to a function by value, returning from a function by value, or catching exceptions by value.

//Direct-initialization is also used when values are explicitly cast to another type 
//(e.g. via static_cast).



//Two types of list initialization
// direct-list-initialization of initial value 5 into variable width (preferred)
int width { 5 }; 
// copy-list-initialization of initial value 6 into variable height (rarely used)   
int height = { 6 }; 




// list-initialization also provides a way to initialize objects with a list of 
//values rather than a single value (which is why it is called “list-initialization”)




// An integer can only hold non-fractional values.
// Initializing an int with fractional value 4.5 requires the compiler to convert 4.5 to a value an int can hold.
// Such a conversion is a narrowing conversion, since the fractional part of the value will be lost.

int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion
int w2 = 4.5;   // compiles: w2 copy-initialized to value 4
int w3 (4.5);   // compiles: w3 direct-initialized to value 4