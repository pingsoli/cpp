# Effective C++ - Third Edition

## Chapter 01 - Accustoming Yourself to C++
[Item 1: View C++ as a federation of languages](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter01/01.cpp)  
[Item 2: Prefer consts, enums, and inlines to #defines](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter01/02.cpp)  
[Item 3: Use const whenever possible](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter01/03.cpp)  
[Item 4: Make sure that objects are initialized before they're used](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter01/04.cpp)  

## Chapter 02 - Constructors, Destructors, and Assignment Operators
[Item 5: Know what functions C++ silently writes and calls](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/05.cpp)  
[Item 6: Explictly disallow the use of compiler-generated functions you do not wnat](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/06.cpp)  
[Item 7: Declare destructors virtual in polymorphic base classes](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/07.cpp)  
[Item 8: Prevent exception from leaving destructors](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/08.cpp)  
[Item 9: Never call virtual functions during construction or destruction](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/09.cpp)  
[Item 10: Have assignment operators return a reference to *this](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/10.cpp)  
[Item 11: Handle assignment to self in operator=](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/11.cpp)  
[Item 12: Copy all parts of an object](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter02/12.cpp)  

## Chapter 03 - Resource Management
[Item 13: Use objects to manage resources](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter03/13.cpp)  
[Item 14: Think carefully about the copying behavior in resource-manageing classes](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter03/14.cpp)  
[Item 15: Provide access to raw resources in resources-managing classes](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter03/15.cpp)  
[Item 16: Use the same form in corresponding uses of new and delete](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter03/16.cpp)  
[Item 17: Store newed objects in smart pointers in standalone statements](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter03/17.cpp)  

## Chapter 04 - Designs and Declarations
[Item 18: Make interfaces easy to use correctly and hard to use incorrectly](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/18.cpp)  
[Item 19: Treat class design as type design](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/19.cpp)  
[Item 20: Prefer pass-by-reference-to-const to pass-by-value](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/20.cpp)  
[Item 21: Don't try to return a reference when you must return a object](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/21.cpp)  
[Item 22: Declare data members private](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/22.cpp)  
[Item 23: Prefer non-member non-friend functions to member functions](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/23.cpp)  
[Item 24: Declare non-member functions when type conversions should apply to all parameters](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/24.cpp)  
[Item 25: Consider support for a non-throwing swap](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter04/25.cpp)  

## Chapter 05 - Implementations
[Item 26: Postpone variable definitions as long as possible](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter05/26.cpp)  
[Item 27: Minimize casting](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter05/27.cpp)  
[Item 28: Avoid returning "handles" to object internals](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter05/28.cpp)  
[Item 29: Strive for exception-safe code](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter05/29.cpp)  
[Item 30: Understand the ins and outs of inlining](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter05/30.cpp)  
[Item 31: Minimize compilation dependencies between files](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter05/31.cpp)  

## Chapter 06 - Inheritance and Object-Oriented Design
[Item 32: Make sure public inheritance models "is-a"](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/32.cpp)  
[Item 33: Avoid hiding inherited names](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/33.cpp)  
[Item 34: Difference between inheritance of interface and inheritance of implementation](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/34.cpp)  
[Item 35: Consider alternatives to virtual functions](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/35.cpp)  
[Item 36: Never redefine an inherited non-virtual function](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/36.cpp)  
[Item 37: Never redefine a function's inherited default parameter value](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/37.cpp)  
[Item 38: Model "has-a" or "is-implemented-in-terms-of" through composition](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/38.cpp)  
[Item 39: Use private inheritance judiciously](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/39.cpp)  
[Item 40: Use multiple inheritance judiciously](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter06/40.cpp)  

## Chapter 07 - Templates and Generic Programming
[Item 41: Understand implicit interfaces and compile-time polymorphism](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/41.cpp)  
[Item 42: Understand two meanings of typename](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/42.cpp)  
[Item 43: Know how to access names in templatized base classes](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/43.cpp)  
[Item 44: Factor parameter-independent code out of templates](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/44.cpp)  
[Item 45: Use member function templates to access "all compatible types"](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/45.cpp)  
[Item 46: Define non-member functions inside templates when type conversions are desired](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/46.cpp)  
[Item 47: Use traits classes for information about types](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/47.cpp)  
[Item 48: Be aware of template metaprogramming](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter07/48.cpp)  

## Chapter 08 - Customing new and delete
[Item 49: ](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter08/49.cpp)  
[Item 50: ](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter08/50.cpp)  
[Item 51: ](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter08/51.cpp)  
[Item 52: ](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter08/52.cpp)  

## Chapter 09 - Miscellany
[Item 53: Pay attention to compiler warnings](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter09/53.cpp)  
[Item 54: Familiarize yourself with the standard library, including TR1](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter09/54.cpp)  
[Item 55: Familiarize yourself with Boost](https://github.com/pingsoli/cpp/blob/master/tutorials/effective_cpp/chapter09/55.cpp)  
