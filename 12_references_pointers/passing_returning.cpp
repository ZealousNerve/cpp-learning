#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <cstddef>   // for std::nullptr_t and NULL


// =============================================================================
// SECTION 1 — THE THREE WAYS TO PASS ARGUMENTS
// =============================================================================

// 1. Pass by value    — a copy of the object is made
// 2. Pass by reference — binds directly to the original object, no copy
// 3. Pass by address  — caller passes the object's address via a pointer;
//                       function receives a COPY of that address (not the object)

void printByValue(std::string val)             { std::cout << val << '\n'; }
void printByReference(const std::string& ref)  { std::cout << ref << '\n'; }
void printByAddress(const std::string* ptr)    { std::cout << *ptr << '\n'; }

// All three print the same thing. But:
// - printByValue    makes an expensive copy of the string
// - printByReference/printByAddress do not — they work on the original
// Since an address is only 4 or 8 bytes, copying a pointer is always cheap.

void section1_demo()
{
    std::string str{ "Hello, world!" };
    printByValue(str);
    printByReference(str);
    printByAddress(&str);    // & gives us the address of str

    // If we already have a pointer, we can pass that too
    std::string* ptr{ &str };
    printByAddress(ptr);
}


// =============================================================================
// SECTION 2 — MODIFYING THE ORIGINAL THROUGH A POINTER
// =============================================================================

// Non-const pointer parameter: function CAN modify the pointed-to object
void changeValue(int* ptr)
{
    *ptr = 6;   // dereference and assign
}

// Const pointer-to-const: function CANNOT modify the pointed-to object
void readOnly(const int* ptr)
{
    // *ptr = 6;  // compile error — good
    std::cout << *ptr << '\n';
}

// BEST PRACTICE on const-ing pointer parameters:
//   - const on the POINTED-TO TYPE (const int*) is significant — tells caller
//     the function won't modify the object. USE THIS.
//   - const on the POINTER ITSELF (int* const) just means the pointer variable
//     inside the function won't be reassigned. Caller doesn't care. AVOID routinely.
//
// Compare:
//   void foo(const char* source, char* dest);              // clear: source=read, dest=write
//   void foo(const char* const source, char* const dest);  // noisy: harder to spot dest is non-const


// =============================================================================
// SECTION 3 — NULL POINTER CHECKING
// =============================================================================

// A null pointer dereference causes undefined behavior (usually a crash).
// Always guard when a pointer parameter might be null.

// Pattern 1: early return
void printSafe_v1(int* ptr)
{
    if (!ptr)
        return;             // bail out immediately if null
    std::cout << *ptr << '\n';
}

// Pattern 2: assert (debug) + early return (release)
void printSafe_v2(const int* ptr)
{
    assert(ptr);    // assert fires in debug builds — documents "this should never be null"
    if (!ptr) return;

    std::cout << *ptr << '\n';
}

// assert is for "things that should never happen" — catching programmer errors.
// The if(!ptr) guard handles the case gracefully in production builds.


// =============================================================================
// SECTION 4 — PREFER PASS BY (CONST) REFERENCE OVER PASS BY ADDRESS
// =============================================================================

// Pass by address only accepts lvalues — rvalues have no address:
//   printByAddress(&5);   // ERROR: can't take address of a literal

// Pass by const reference accepts both lvalues and rvalues:
void printByRef(const int& ref) { std::cout << ref << '\n'; }

void section4_demo()
{
    int x{ 5 };
    printByRef(x);  // lvalue — fine
    printByRef(5);  // rvalue — also fine with const ref, NOT fine with pass-by-address
}

// Pass by reference also avoids the & and * clutter in your code.
// RULE: "Pass by reference when you can, pass by address when you must."


// =============================================================================
// SECTION 5 — OPTIONAL ARGUMENTS USING POINTER DEFAULT = nullptr
// =============================================================================

// One legitimate use of pass by address: making a parameter optional
void printIDNumber_v1(const int* id = nullptr)
{
    if (id)
        std::cout << "Your ID is " << *id << ".\n";
    else
        std::cout << "Your ID is not known.\n";
}

// But function overloading is usually cleaner — no null risk, accepts rvalues too
void printIDNumber_v2()                { std::cout << "Your ID is not known\n"; }
void printIDNumber_v2(int id)          { std::cout << "Your ID is " << id << "\n"; }

void section5_demo()
{
    printIDNumber_v1();             // uses nullptr default
    int userid{ 34 };
    printIDNumber_v1(&userid);

    printIDNumber_v2();             // overload version — cleaner
    printIDNumber_v2(34);
    printIDNumber_v2(62);           // rvalue works here, wouldn't with pointer version
}


// =============================================================================
// SECTION 6 — CHANGING WHAT A POINTER POINTS AT
// =============================================================================

// Passing a pointer to a function passes a COPY of the pointer.
// Changing what the copy points at does NOT affect the original pointer.

void nullify_doesnt_work(int* ptr2)
{
    ptr2 = nullptr;    // only changes the local copy — original ptr is unaffected
}

// To actually change what the original pointer points at, pass the pointer BY REFERENCE:
void nullify_works(int*& refptr)    // int*& = "reference to a pointer to int"
{
    refptr = nullptr;   // modifies the original pointer
}

void section6_demo()
{
    int x{ 5 };
    int* ptr{ &x };

    nullify_doesnt_work(ptr);
    std::cout << (ptr ? "non-null" : "null") << '\n';   // non-null — ptr unchanged

    nullify_works(ptr);
    std::cout << (ptr ? "non-null" : "null") << '\n';   // null — ptr was changed
}

// SYNTAX NOTE:
//   int*&  = reference to a pointer  — VALID, this is what you want
//   int&*  = pointer to a reference  — ILLEGAL (references aren't objects, have no address)
// If you write it backwards, the compiler will error and you'll know to flip it.


// =============================================================================
// SECTION 7 — WHY nullptr, NOT 0 OR NULL
// =============================================================================

void print_int(int x)   { std::cout << "print(int): "  << x << '\n'; }
void print_ptr(int* ptr){ std::cout << "print(int*): " << (ptr ? "non-null" : "null") << '\n'; }

void section7_demo()
{
    int x{ 5 };
    int* ptr{ &x };

    print_ptr(ptr);     // always calls print(int*) — correct
    print_int(0);       // always calls print(int)  — 0 is an integer literal

    // print_int(NULL); // DANGEROUS: NULL might be 0 (calls print(int)), or
                        // ((void*)0), or something else — behavior varies by compiler/platform

    print_ptr(nullptr); // always calls print(int*) — unambiguous, always correct
}

// NULL is a preprocessor macro — its definition is implementation-defined.
// 0 can be interpreted as integer OR null pointer — ambiguous in overloads.
// nullptr has its own type (std::nullptr_t) and only matches pointer parameters.
// ALWAYS use nullptr for null pointers.


// =============================================================================
// SECTION 8 — std::nullptr_t (THE TYPE OF nullptr)
// =============================================================================

// nullptr has type std::nullptr_t. You can write a function that accepts ONLY nullptr:

void print_nullptrT(std::nullptr_t) { std::cout << "got nullptr_t\n"; }
void print_nullptrT(int*)           { std::cout << "got int*\n"; }

void section8_demo()
{
    print_nullptrT(nullptr);    // calls print(std::nullptr_t)

    int x{ 5 };
    int* ptr{ &x };
    print_nullptrT(ptr);        // calls print(int*) — type is int*, regardless of value

    ptr = nullptr;
    print_nullptrT(ptr);        // STILL calls print(int*) — overloading matches on TYPE, not VALUE
                                // ptr's type is int*, not nullptr_t, even though it holds nullptr
}


// =============================================================================
// SECTION 9 — THERE IS ONLY PASS BY VALUE (CONCEPTUAL MODEL)
// =============================================================================

// Pass by reference is implemented by the compiler using pointers internally.
// Pass by address copies an address (a value) from caller to function.
// Therefore: EVERYTHING in C++ is ultimately pass by value.
//
// The power of pass-by-reference/address comes from the ability to DEREFERENCE
// the address and reach the original object — something a plain value copy can't do.
// There's no magic, just pointer mechanics under the hood.


// =============================================================================
// SECTION 10 — RETURN BY REFERENCE
// =============================================================================

// Returning a class type by value makes a copy — expensive for large objects.
// Return by reference returns a reference bound to an existing object — no copy.

//   std::string  returnByValue();            // returns a copy — expensive
//   std::string& returnByRef();              // returns a reference — cheap
//   const std::string& returnByConstRef();   // returns a const reference — cheap

// VALID: returning a static local variable — it lives until the program ends
const std::string& getProgramName()
{
    static const std::string s_programName{ "Calculator" };
    return s_programName;   // safe: s_programName outlives this function call
}

// INVALID: returning a non-static local variable — it's destroyed when the function returns
// const std::string& getBroken()
// {
//     const std::string name{ "Calculator" };
//     return name;    // DANGLING REFERENCE — undefined behavior
// }                   // name is destroyed here

// RULE: The object being returned by reference MUST outlive the function.
//       NEVER return a (non-static) local variable or temporary by reference.


// =============================================================================
// SECTION 11 — LIFETIME EXTENSION DOES NOT CROSS FUNCTION BOUNDARIES
// =============================================================================

// Normally, binding a const reference to a temporary extends the temporary's lifetime.
// This ONLY works at the point of direct binding — it does NOT work through functions.

const int& returnTempRef()
{
    return 5;   // creates a temporary, returns reference to it
}               // temporary is destroyed here

// BROKEN:
// const int& ref{ returnTempRef() };  // ref is dangling — temporary already gone

// Also broken (less obviously):
const int& passThrough(const int& ref) { return ref; }

void section11_demo()
{
    const int& ref1{ 5 };               // OK — direct binding extends lifetime
    // const int& ref2{ passThrough(5) }; // NOT OK — bounced through function, lifetime not extended
    // std::cout << ref2;               // undefined behavior

    std::cout << ref1 << '\n';          // fine
}


// =============================================================================
// SECTION 12 — GOTCHA: NON-CONST STATIC RETURNED BY REFERENCE
// =============================================================================

// All callers share the same static variable. Mutations affect everyone.

const int& getNextId()
{
    static int s_x{ 0 };
    ++s_x;
    return s_x;
}

void section12_demo()
{
    // WRONG — both are references to the SAME static variable
    const int& id1{ getNextId() };  // s_x is now 1, id1 references it
    const int& id2{ getNextId() };  // s_x is now 2, id2 also references it
    std::cout << id1 << id2 << '\n';    // prints 22 — both see current value of s_x (2)

    // CORRECT — copy the value out into a normal variable
    const int id3{ getNextId() };   // s_x is now 3, id3 holds a COPY of 3
    const int id4{ getNextId() };   // s_x is now 4, id4 holds a COPY of 4
    std::cout << id3 << id4 << '\n';    // prints 34 — independent copies
}

// BEST PRACTICE: Avoid returning non-const static local variables by reference.
// Returning a const reference to a const static is acceptable (e.g. expensive-to-create objects).


// =============================================================================
// SECTION 13 — RETURNING REFERENCE PARAMETERS BY REFERENCE (ALWAYS SAFE)
// =============================================================================

// If a parameter came in by reference, the original object lives in the caller's scope.
// It's safe to return it by reference — the object will still exist after the function returns.

const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
    return (a < b) ? a : b;     // safe: a and b live in the caller
    //a and b are born outside the function, so no static is needed because their lifetime is controlled by the caller.
}

void section13_demo()
{
    std::string hello{ "Hello" };
    std::string world{ "World" };
    std::cout << firstAlphabetical(hello, world) << '\n';   // Hello

    // This avoids up to 3 copies that pass-by-value / return-by-value would make.
}


// =============================================================================
// SECTION 14 — CALLER CAN MODIFY THROUGH A RETURNED NON-CONST REFERENCE
// =============================================================================

int& maxOf(int& x, int& y)
{
    return (x > y) ? x : y;    // returns reference to whichever is larger
}

void section14_demo()
{
    int a{ 5 }, b{ 6 };
    maxOf(a, b) = 7;    // maxOf returns reference to b, then assigns 7 through it
                        // effectively: b = 7
    std::cout << a << b << '\n';    // 57
}


// =============================================================================
// SECTION 15 — RETURN BY ADDRESS
// =============================================================================

// Works like return by reference but returns a pointer.
// Same rule: the object being pointed at must outlive the function.

// The KEY advantage over return by reference:
//   You can return nullptr to signal "no valid object found"

struct Student { int id; std::string name; };

Student* findStudent(Student* arr, int size, int targetId)
{
    for (int i = 0; i < size; ++i)
        if (arr[i].id == targetId)
            return &arr[i];     // found — return pointer to the element
    return nullptr;             // not found — nullptr is a valid meaningful return
}

void section15_demo()
{
    Student students[]{ {1, "Alice"}, {2, "Bob"}, {3, "Carol"} };

    Student* found = findStudent(students, 3, 2);
    if (found)                          // ALWAYS null-check before dereferencing
        std::cout << found->name << '\n';   // Bob
}

// Downside: caller must always null-check or risk undefined behavior.
// BEST PRACTICE: Prefer return by reference. Use return by address only when
//                returning nullptr is a meaningful "no result" signal.


// =============================================================================
// SECTION 16 — IN PARAMETERS (normal case)
// =============================================================================

// A parameter used only to receive input. The normal, default case.
// Pass by value for small/cheap types, pass by const reference for large/expensive types.

void print_in(int x)               { std::cout << x << '\n'; }          // in-param, by value
void print_in(const std::string& s){ std::cout << s << '\n'; }          // in-param, by const ref


// =============================================================================
// SECTION 17 — OUT PARAMETERS
// =============================================================================

// A parameter used to send data BACK to the caller (instead of, or in addition to,
// a return value). Done via non-const reference or pointer-to-non-const.

// Convention: name out-parameters with "Out" suffix so callers know the
// initial value doesn't matter and will be overwritten. Place them last.

void getSinCos(double degrees, double& sinOut, double& cosOut)
{
    constexpr double pi{ 3.14159265358979323846 };
    double radians{ degrees * pi / 180.0 };
    sinOut = std::sin(radians);
    cosOut = std::cos(radians);
}

void section17_demo()
{
    double s{ 0.0 }, c{ 0.0 };
    getSinCos(45.0, s, c);
    std::cout << "sin=" << s << " cos=" << c << '\n';
}

// DOWNSIDES of out parameters:
//
// 1. Caller must pre-create variables (can't be const, can't be used as temporaries):
//      int y{};
//      getByReference(y);      // awkward two-step
//      std::cout << y;
//
//    vs return by value:
//      std::cout << getByValue();   // clean, works inline
//
// 2. Call site doesn't show which args are modified:
//      getSinCos(degrees, sin, cos);   // are sin/cos being read? written? unclear.
//    vs:
//      x = foo();   // obviously x is being changed


// =============================================================================
// SECTION 18 — IN/OUT PARAMETERS
// =============================================================================

// A parameter that is both read (in) and written back (out).
// Same mechanics and downsides as out parameters.

// A good function name signals to the caller that the argument will be mutated:
void doubleValue(int& inout)
{
    inout *= 2;
}

// Alternative: pass by value/const-ref, return new value — more conventional syntax
int doubleValue_conventional(int in)
{
    return in * 2;
}

void section18_demo()
{
    int x{ 5 };
    doubleValue(x);                     // x is now 10 — mutation not obvious at call site
    std::cout << x << '\n';

    x = doubleValue_conventional(x);    // obvious: x is being replaced
    std::cout << x << '\n';             // 20
}


// =============================================================================
// SECTION 19 — WHEN TO ACTUALLY USE PASS BY NON-CONST REFERENCE
// =============================================================================

// AVOID out/in-out parameters unless you have a good reason.
// The two justified exceptions:

// 1. In/out: modifying an existing object in place is simpler and avoids copies
//    (name the function to make the mutation obvious)

// 2. Performance-critical code where copying the return object is genuinely expensive,
//    and the function is called very frequently (e.g. filling large arrays/buffers)
//
//    void generateExpensiveData(LargeArray& out)
//    {
//        // fill out — avoids an expensive copy on return
//    }

// In all other cases, prefer returning by value. Modern compilers often optimize
// away the extra copies anyway (Return Value Optimization / copy elision).


// =============================================================================
// QUICK REFERENCE SUMMARY
// =============================================================================
//
// PASSING:
//   Pass by value           — copies; cheap for small types; no modify
//   Pass by const ref       — no copy; no modify; accepts lvalues + rvalues
//   Pass by non-const ref   — no copy; CAN modify; lvalues only
//   Pass by const ptr       — no copy; no modify; lvalues only; can be null
//   Pass by non-const ptr   — no copy; CAN modify; lvalues only; can be null
//
// RETURNING:
//   Return by value         — copy; always safe
//   Return by const ref     — no copy; no modify; object must outlive function
//   Return by non-const ref — no copy; CAN modify; object must outlive function
//   Return by address       — no copy; can return nullptr; object must outlive function
//
// RULES TO INTERNALIZE:
//   1. Never return a reference or pointer to a non-static local variable.
//   2. Lifetime extension does NOT cross function boundaries.
//   3. Always use nullptr — never 0 or NULL.
//   4. Reference to pointer syntax: int*& (not int&* — that's illegal).
//   5. Overload resolution matches on TYPE, not value. ptr=nullptr is still type int*.
//   6. Non-const static returned by reference: all callers share the same object.
//   7. Avoid out parameters — prefer return by value when possible.
//   8. "Pass by reference when you can, pass by address when you must."
//   9. Under the hood, everything is pass by value — references are pointer mechanics.


// =============================================================================
int main()
{
    section1_demo();
    section4_demo();
    section5_demo();
    section6_demo();
    section7_demo();
    section8_demo();
    section11_demo();
    section12_demo();
    section13_demo();
    section14_demo();
    section15_demo();
    section17_demo();
    section18_demo();
    return 0;
}