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

#### Item 8: Prefer nullptr to 0 and NULL.
1) Prefer nullptr to 0 and NULL.
2) Avoid overloading on integral and pointer types.

#### Item 9: Prefer alias declarations to typedefs.
1) typedefs don't support templatization, but alias declaration do.
2) Alias templates avoid the "::type" suffix and, in templates, the "typename"
prefix often required to refer to typedefs.
3) C++14 offers alias template for all the C++11 type traits transformation.

#### Item 10: Prefer scoped enums to unscoped enums.
1) C++98-style enums are now known as unscoped enums.
2) Enumerators of scoped enums are visible only within the enum. They convert
to other types only with cast.
3) Both scoped and unscoped enums support specification of the underlying type.
the default underlying type for scoped enums is int. Unscoped enums have no
default Underlying type.
4) Scoped enums may always be forward-declared. Unscoped enums may be
forward-declared only if their declaration specifies an underlying type.

#### Item 11: Prefered deleted functions to private undefined ones.
1) Prefer deleted functions to private undefined ones.
2) Any function may be deleted, including non-member functions and template
instantiations.

#### Item 12: Declare overriding functions override.
1) Declare overriding functions override.
2) Member function reference qualifiers make it possible to treat lvalue and
rvalue object(`*`this) differently.

#### Item 13: Prefer const_iterator to iterator.
1) Prefer const_iterator to iterator.
2) In maximally generic code, prefer non-member versions of begin, end, rbegin,
etc., over the member function counterparts.

In C-style code, you can use begin(), end() methods to get the first or end element
from a array, it's more generic.

#### Item 14: Declare functions if they won't emit exceptions.
1) noexcept is part of a function's interface, and that means that callers may
depend on it.
2) noexcept functions are more optimizable than non-except functions.
3) noexcept is particularly valuable for the move operations, swap, memory
deallocation functions, and destructors.
4) Most functions are exception-neutral rather than noexcept.

#### Item 15: Use constexpr whenever possible.
1) constexpr objects are const and are initialized with values known during
compilation.
2) constexpr functions can produce compile-time results when called with
arguments whose values are known during compilation.
3) constexpr object and functions may be used in wide range of contexts than
non-constexpr objects and functions.
4) constexpr is part of an object's or function's interface.

#### Item 16: Make const member functions thread safe.
1) Make const member functions thread safe unless you're certain they'll never
be used in a concurrent context.
2) Use of std::atomic variable may offer better performance than a mutex, but
they're suited for mainipulation of only a single variable or memory location.

#### Item 17: Understand special member function generation.
1) The special member functions are those compiler may generate on their own:
default constructor, destructor, copy operations, move operations.
2) Move operations are generated only for classes lacking explicitly
declared move operations, copy operations, and a destructor.
3) The copy constructor is generated only for classes lacking an explicitly
declared copy constructor, and it's deleted if a move operation is declared.
The copy assignment operator is generated only for classes lacking an explicitly
declared copy assignment operator, and it's deleted if a move operation is
declared. Generation of the copy operations in classes with an explicitly
declared destructor is deprecated.
4) Member function templates never suppress generation of special member functions.

### Chapter 4: Smart Pointers
#### Item 18: Use std::unique_ptr for exclusive-ownership resource management.
1) std::unique_ptr is a small, fast, move-only smart pointer for managing
resource with exclusive-ownership semantics.
2) By default, resource destruction takes place via delete, but custom deleters
can be specified. Stateful deleters and function pointers as deleters increase
the size of std::unique_ptr objects.
3) Converting std::unique_ptr to a std::shared_ptr is easy.

#### Item 19:
#### Item 20:
#### Item 21:
#### Item 22:

### Chatper 5: Rvalue References, Move Semantics, and Perfect Forwarding

### Chapter 6: Lambda Expression

### Chapter 7: The Concurrency API

### Chapter 8: Tweaks

