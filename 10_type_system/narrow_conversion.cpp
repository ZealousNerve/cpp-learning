/*The following conversions are defined to be narrowing:

* From a floating point type to an integral type.

* From a floating point type to a narrower or lesser ranked floating point type, unless the value being converted is
  constexpr and is in range of the destination type (even if the destination type doesn’t have the precision to store
  all the significant digits of the number).

* From an integral to a floating point type, unless the value being converted is constexpr and whose value can be
  stored exactly in the destination type.

* From an integral type to another integral type that cannot represent all values of the original type, unless the
  value being converted is constexpr and whose value can be stored exactly in the destination type. This covers both
  wider to narrower integral conversions, as well as integral sign conversions (signed to unsigned, or vice-versa).*/



 /*implicit narrowing conversions will result in compiler warnings, except signed/unsigned conversions
 (which may or may not produce warnings, depending on how your compiler is configured).

Because they can be unsafe and are a source of errors, avoid narrowing conversions whenever possible

as narrow conversion is not always avoidable and hence we should use static cast to show and document that this
conversion is intentional and therefore no compiler warning will be there

as we know, brace initialization doesn't support narrow conversion, we should use static cast inside the braces while
initialization to carry out narrow conversion in braces*/


/*some constexpr aren't considered narrow conversion

When the source value of a narrowing conversion is constexpr, the specific value to be converted must be known
to the compiler. In such cases, the compiler can perform the conversion itself, and then check whether the value
was preserved. If the value was not preserved, the compiler can halt compilation with an error. If the value is
preserved, the conversion is not considered to be narrowing (and the compiler can replace the entire conversion
with the converted result, knowing that doing so is safe).*/

#include <iostream>

int main()
{
  constexpr int n1{ 5 };   // note: constexpr
  unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause

  constexpr int n2 { -5 }; // note: constexpr
  unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change



/*Strangely, conversions from a floating point type to an integral type do not have a constexpr exclusion clause,
so these are always considered narrowing conversions even when the value to be converted is constexpr and fits in
the range of the destination type:*/

  int n { 5.0 }; // compile error: narrowing conversion


/*Even more strangely, conversions from a constexpr floating point type to a narrower floating point type are not
considered narrowing even when there is a loss of precision!  */

  constexpr double d { 0.1 };
  float f { d }; // not narrowing, even though loss of precision results

  return 0;
}
