/*The condition in a switch must evaluate to an integral type or an enumerated type, or be convertible to one.
Expressions that evaluate to floating point types, strings, and most other non-integral types may not be used here.*/
#include <iostream>
void printDigitName(int x){
    switch (x){ // x evaluates to 3
        int a; // okay: definition is allowed before the case labels
        //int b{ 5 }; // illegal: initialization is not allowed before the case labels

        case 1:
            int y; // okay but bad practice: definition is allowed within a case
            y = 4; // okay: assignment is allowed
            std::cout << "One" << y;
            break;
        case 2:
            std::cout << "Two";
            [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement

            /*here above we haven't used break statement, and that's why if this command executes then all the next
            commands also execute until the next break or return is encountered, and upon not using break statement
            the compiler will pop a warning about this, and that's why we are using a fallthrough attribute with ;

            Use the [[fallthrough]] attribute (along with a null statement) to indicate intentional fallthrough.
            and compiler will not give any warning*/


        case 3:
            //int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
            y = 5; // okay: y was declared above, so we can use it here too
            std::cout << "Three"; // execution starts here
            break; // jump to the end of the switch block
        default:
            std::cout << "Unknown";
            break;
    }
    // execution continues here
    std::cout << " Ah-Ah-Ah!";
}
/*we can use return instead of break, return throws us outside the function whereas the break is same as return just
it keeps us in the same block not throw outside

with switch statements, the statements after labels are all scoped to the switch block. No implicit blocks are created.*/
