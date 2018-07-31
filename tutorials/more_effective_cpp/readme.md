# More Effective Cpp

## Basics
#### Item 1: Distinguish between pointers and references.
there is no such thing as a null reference.  
no need to check reference is null, but pointers must check before using it.  

#### Item 2: Prefer C++ style casts.
static_cast<type>(expression)  
dynamic_cast<type>(expression)  
reinterpret_cast<type>(expression)  
const_cast<type>(expression)  

#### Item 3: Never treat arrays polymorphically.
#### Item 4: Avoid gratuitous default constructors.

## Operators
#### Item 5: Be wary of user-defined conversion functions.
#### Item 6: Distinguish between prefix and postfix forms of increment and decrement.
#### Item 7: Never overload "&&", "||", or ",".
#### Item 8: Understand the different meanings of new and delete.

## Exceptions
#### Item 9: Use destructors to prevent resource leaks.
#### Item 10: Prevent resource leaks in constructors.
use smart pointer, such as std::unique_ptr, ans shared_ptr.  

#### Item 11: Prevent exceptions from leaving destructors.
1) destrcutors swallow the exception.  
2) use another function to do cleaning up.  

#### Item 12: Understand how throwing an exception differs from passing a parameter or calling a virtual function.
#### Item 13: Catch exceptions by reference.
Throw by value, catch by reference.  

#### Item 14: Use exception specifications judiciousy.
you can throw any type exception value or no exception.  
make sure you understand the stack unwinding.  
you can know the what happens when exception occuring.  

#### Item 15: Understand the costs of exception handling.
for readability, exception is good thing to detect the error.  
with modern architecture, the zero-cost model exceptions is possible.  

## Effiency
#### Item 16: Remember the 80-20 rule.
80 percent of a programs are used by about 20 percent of the code.  

#### Item 17: Consider using lazy evaluation.
#### Item 18: Amortize the cost of excepted computations.
#### Item 19: Understand the origin of temporary objects.
user-defined swap function is good example.  
overloading operator operators, such as operator+.  
const Number operator+(const Number& lhs, const Number& rhs)  

#### Item 20: Facilitate the return value optimization.
return value optimization and the compiler.  
the compiler will not guarantee the RVO, but may allows it.  

#### Item 21: Overload to avoid implicit type conversions.
#### Item 22: Consider using op= instead of stand-alone op.
#### Item 23: Consider alternative libraries.
#### Item 24: Understand the costs of virtual functions, multiple inheritance, virtual base classes, and RTTI.

## Techniques
#### Item 25: Virtualizing constructors and non-member functions.
#### Item 26: Limiting the number of objects of a class.
#### Item 27: Requiring or prohibiting heap-based objects.

#### Item 28: Smart pointers.
NOTE: don't use auto_ptr, it's old-fashioned. use unique_ptr and shared_ptr instead.  

#### Item 29: Reference counting.
#### Item 30: Proxy classes.
three examples:  
1) Multidimensional arrays.  
2) lvalue/rvalue differences.  
3) suppression of implicit conversions.  

disadvantages:  
1) temporaries is inevitable, it costs too much.  
2) increase the complexity of software system.  

#### Item 31: Making functions virutal with respect to more than one object.

## Miscellany
#### Item 32: Program in the future tense.
1) Provide complete classes.
2) Design your interfaces to facilitate common operations and prevent common errors.

#### Item 33: Make non-leaf classes abstract.
#### Item 34: Understand how to combine c++ and C in the same program.
1) Make sure the C++ and C compilers produce compatible object files.
2) Declare functions to be used by both languages extern "C".
3) If at all possible, write main in C++.
4) Always use delete with memory from new, always use free with memory from malloc.
5) Limit what you pass between the two languages to data structures that compile under C;
the C++ version of structs may contain non-virutal member functions.

#### Item 35: Familiarize yourself with the language standard.
throw away the old C-style fashion.  
familiarize STL (Standard Template Library).  
