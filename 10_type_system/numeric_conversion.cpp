//there are five basic types of numeric conversion:

//1. Converting an integral type to any other integral type (excluding integral promotions):
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = s; // convert short to char
unsigned int u = 3; // convert int to unsigned int

//2. Converting a floating point type to any other floating point type (excluding floating point promotions):
float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double

//3. Converting a floating point type to any integral type:
int i = 3.5; // convert double to int

//4. Converting an integral type to any floating point type:
double d = 3; // convert int to double

//5. Converting an integral type or a floating point type to a bool:
bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool

//we have used copy initialization in above statements as list initialization disallows certain type of conversions

/*Unlike numeric promotions (which are always value-preserving and thus “safe”), many numeric conversions are unsafe.
An unsafe conversion is one where at least one value of the source type cannot be converted into an equal value of
the destination type.

Numeric conversions fall into three general safety categories:

1. Value-preserving conversions are safe numeric conversions where the destination type can exactly
   represent all possible values in the source type.

2. Reinterpretive conversions are unsafe numeric conversions where the converted value may be different from the
   source value, but no data is lost. Signed/unsigned conversions fall into this category.

   e.g. A unsigned converted to signed will not cause an issue, but if a signed is converted to unsigned then the result
   is modulo wrapped of the original one, but in both the case when again converted to the source the value remains the
   same so no data lost in this category also

3. Lossy conversions are unsafe numeric conversions where data may be lost during the conversion.
   e.g. float to int or double to float, data will be lost


*/

