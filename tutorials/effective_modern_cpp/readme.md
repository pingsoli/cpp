# Effective Modern C++

### Chapter 1: Deducing Types
#### Item 1: Understand template type deduction.
```
template <typename T>
void f(ParamType param);

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void f(T& param); // param is reference

int x = 27;         // x is an int.
const int cx = x;   // cx is a const int.
const int& rx = x;  // rx is a reference to x as a const int.

f(x);   // T is int, param's type is int&.
f(cx);  // T is const int, param's type is const int&.
f(rx);  // T is const int, param's type is const int&.

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void f(const T& param); // param is now ref-to-const

f(x);   // T is int, param's type is const int&.
f(cx);  // T is int, param's type is const int&.
f(rx);  // T is int, param's type is const int&.

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void f(T&& param); // param is now a universal reference.

f(x);   // x is lvalue, so T is int&, param's type is also int&.
f(cx);  // cx is lvalue, so T is const int&, param's type is also const int&.
f(rx);  // rx is lvalue, so T is const int&, param's type is also const int&.
f(27);  // 27 is rvalue, so T is int, param's type is therefore int&&.

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void f(T param); // param is now passed by value.

f(x);   // T's and param's types are both int.
f(cx);  // T's and param's types are again both int.
f(rx);  // T's and param's types are still both int.
```
1) During template type deduction, arguments that are references are treated as
non-references, i.e., their reference-ness is ignored.
2) When deducing types for universal reference parameters, lvalue arguments get
special treatment.
3) When deducing types for by-value paramters, const and/or volatile arguments
are treated as non-const and non-volatile.
4) During template type deduction, arguments that are array or function names
decay to pointers, unless they're used to initialize references.

#### Item 2: Understand auto type deduction.
1) auto type deduction is usually the same as template type deduction, but auto
type deduction assumes that a braced initializer represents std::initializer_list
, and template type deduction doesn't.
2) auto in a function return type or a lambda paramter impiles template type
deduction, not auto type deduction.

#### Item 3: Understand decltype.
1) decltype almost always yields the type of a variable or expression without
any modifications.
2) For lvalue expressions of type T other than names, decltype always reports a
type of T&.
3) C++14 supports decltype(auto), which like auto, deduces a type from its
initializer, but it performs the type deduction using the decltype rules.

#### Item 4: Know how to view deduced types.
1) Deduced types can often be seen using IDE editors, compiler error messages,
and the Boost TypeIndex library.
2) The result of some tools may be neither helpful nor accurate, so an understanding
of C++'s type deduction rules remain essential.

### Chapter 2: auto
#### Item 5: Prefer auto to explicit type declarations.
1) auto variables must be initialized, are generally immune to type mismatches
that can lead to portability or efficiency problems, can ease the process of
refactoring, and typically require less typing than variables with explicitly
specified types.

#### Item 6: Use the explicity typed initializer idiom when auto deduces undesired types.
1) "Invisible" proxy types can cause auto to deduce the "wrong" type of an initializing expression.
2) The explicitly typed initialzer idiom forces auto to deduce the type you want it to have.
```
auto index = static_cast<int>(d * c.size());
```

### Chapter 3: Moving to modern C++
#### Item 7: Distinguish between () and {} when creating objects.
1) Braced initialization is the most usable initialization syntax, it prevents
narrowing conversions, and it's immune to C++'s most vexing parse.
2) During constructor overload resolution, braced initializers are matched to
std::initializer_list parameter if at all possible, even if other constructors
offer seemingly better matches.
3) An example of where the choice between parantheses and braces can make a
significant difference is creating a std::vector`<numeric type>` with two arguments.
4) Choosing between parantheses and braces for object creation inside templates
can be challenging.

#### Item 8:
#### Item 9:
#### Item 10:
#### Item 11:
#### Item 12:
#### Item 13:
#### Item 14:
#### Item 15:
#### Item 16:
#### Item 17:

### Chapter 4: Smart Pointers

### Chatper 5: Rvalue References, Move Semantics, and Perfect Forwarding

### Chapter 6: Lambda Expression

### Chapter 7: The Concurrency API

### Chapter 8: Tweaks

