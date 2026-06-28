//BOOLEAN DATATYPES:

//Boolean variables are variables that can have only two possible values: true, and false.
#include <iostream>

int main() {
 bool b1 { true };
 bool b2 { false };
 b1 = false;
 bool b3 {}; // default initialize to false

 //the logical NOT operator (!) can be used to flip a Boolean value from true to false, or false to true.
 //true is stored as integer 1, and false is stored as integer 0

 //If you want std::cout to print true or false instead of 0 or 1, you can output std::boolalpha

 std::cout << true << '\n'; //print 1
 std::cout << false << '\n'; //print 0

 std::cout << std::boolalpha; // print bools as alphabets i.e. true or false

 std::cout << true << '\n'; //print true
 std::cout << false << '\n'; //print false

 std::cout << std::noboolalpha; //again print bools as 1 & 0

 std::cout << true << '\n'; //print 1
 std::cout << false << '\n'; //print 0

 //can initialize using 1 & 0 also
   bool bFalse { 0 }; // okay: initialized to false
   bool bTrue  { 1 }; // okay: initialized to true
 //bool bNo    { 2 }; // error: narrowing conversions disallowed

 /*above narrowing conversions are disallowed but if we use copy initailization where narrowing is allowed we will get 0
 for false and any other integer as true*/

 /*By default, std::cin only accepts numeric input for Boolean variables: 0 is false, and 1 is true. Any other numeric
  value will be interpreted as true, and will cause std::cin to enter failure mode. Any non-numeric value will be
  interpreted as false and will cause std::cin to enter failure mode.

 To allow std::cin to accept the words false and true as inputs, you must first input to std::cin >> std::boolalpha;

 // Allow the user to input 'true' or 'false' for boolean values
 // This is case-sensitive, so True or TRUE will not work
 std::cin >> std::boolalpha;
 std::cin >> b;

 However, when std::boolalpha is enabled for input, numeric values will no longer be accepted
 (they evaluate to false and cause std::cin to enter failure mode).
 */



 //CHAR DATATYPES:

 /*


 complete ASCII table:

 Code  Symbol                          Code  Symbol  Code  Symbol  Code  Symbol
 0     NUL (null)                      32    (space) 64    @       96    `
 1     SOH (start of header)           33    !       65    A       97    a
 2     STX (start of text)             34    "       66    B       98    b
 3     ETX (end of text)               35    #       67    C       99    c
 4     EOT (end of transmission)       36    $       68    D       100   d
 5     ENQ (enquiry)                   37    %       69    E       101   e
 6     ACK (acknowledge)               38    &       70    F       102   f
 7     BEL (bell)                      39    '       71    G       103   g
 8     BS (backspace)                  40    (       72    H       104   h
 9     HT (horizontal tab)             41    )       73    I       105   i
 10    LF (line feed/new line)         42    *       74    J       106   j
 11    VT (vertical tab)               43    +       75    K       107   k
 12    FF (form feed/new page)         44    ,       76    L       108   l
 13    CR (carriage return)            45    -       77    M       109   m
 14    SO (shift out)                  46    .       78    N       110   n
 15    SI (shift in)                   47    /       79    O       111   o
 16    DLE (data link escape)          48    0       80    P       112   p
 17    DC1 (data control 1)            49    1       81    Q       113   q
 18    DC2 (data control 2)            50    2       82    R       114   r
 19    DC3 (data control 3)            51    3       83    S       115   s
 20    DC4 (data control 4)            52    4       84    T       116   t
 21    NAK (negative acknowledge)      53    5       85    U       117   u
 22    SYN (synchronous idle)          54    6       86    V       118   v
 23    ETB (end of transmission block) 55    7       87    W       119   w
 24    CAN (cancel)                    56    8       88    X       120   x
 25    EM (end of medium)              57    9       89    Y       121   y
 26    SUB (substitute)                58    :       90    Z       122   z
 27    ESC (escape)                    59    ;       91    [       123   {
 28    FS (file separator)             60    <       92    \       124   |
 29    GS (group separator)            61    =       93    ]       125   }
 30    RS (record separator)           62    >       94    ^       126   ~
 31    US (unit separator)             63    ?       95    _       127   DEL (delete)




 Codes 0-31 and 127 are called the unprintable chars. These codes were designed to control peripheral devices such as
 printers (e.g. by instructing the printer how to move the print head). Most of these are obsolete now. If you try to
 print these chars, the results are dependent upon your OS (you may get some emoji-like characters).

 Codes 32-126 are called the printable characters, and they represent the letters, number characters, and punctuation
 that most computers use to display basic English text.

 If you try to print a character whose value is outside the range of ASCII, the results are also dependent upon your OS.
  */

 char ch{5}; // initialize with integer 5 (stored as integer 5)
 char ch1{'5'}; // initialize with code point for '5' (stored as integer 53)



 std::cout << "Input a keyboard character: "; // assume the user enters "abcd" (without quotes)

 char ch2{};
 std::cin >> ch; // ch = 'a', "bcd" is left queued.
 std::cout << "You entered: " << ch << '\n';

 // Note: The following cin doesn't ask the user for input, it grabs queued input!
 std::cin >> ch; // ch = 'b', "cd" is left queued.
 std::cout << "You entered: " << ch << '\n';


 /*
 we know std::cin ignores whitespace, but whitespace is still a char, so ignoring it is not what we want, so to resolve it
 we will use std::cin.get(ch)

  */

 /*
 ESCAPE SEQUENCE:

 Name               Symbol       Meaning
 Alert              \a           Makes an alert, such as a beep
 Backspace          \b           Moves the cursor back one space
 Formfeed           \f           Moves the cursor to next logical page
 Newline            \n           Moves cursor to next line
 Carriage return    \r           Moves cursor to beginning of line
 Horizontal tab     \t           Prints a horizontal tab
 Vertical tab       \v           Prints a vertical tab
 Single quote       \'           Prints a single quote
 Double quote       \"           Prints a double quote
 Backslash          \\           Prints a backslash
 Question mark      \?           Prints a question mark (legacy escape; usually not needed)
 Octal number       \nnn         Character represented by an octal value
 Hex number         \xnn         Character represented by a hexadecimal value
  */
}