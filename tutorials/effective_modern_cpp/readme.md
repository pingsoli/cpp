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

#### Item 19: Use std::shared_ptr for shared-ownership resource management.
1) std::shared_ptr offer convenience approaching that of garbage collection
for the shared lifetime management of arbitrary resources.
2) Compared to std::unique_ptr, std::shared_ptr objects are typically twice
as big, incur overload of control blocks, and require atomic reference count
manipulates.
3) Default resource destruction is via delete, but custom deleters are supported.
the type of the deleter has no effect on the type of the std::shared_ptr.
4) Avoid creating std::shared_ptrs from variables of raw pointer type.

#### Item 20: Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.
1) Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.
2) Potential use cases for std::weak_ptr include caching, observer list, and the
prevention of std::shared_ptr cycles.

#### Item 21: Prefer std::make_unique and std::make_shared to direct use of new.
1) Compared to direct use of new, make functions elimiante source code
duplication, improve exception safety, and, for std::make_shared and
std::allocate_shared, generate code that's faster and smaller.
2) Situations where use of make functions is inappropriate include the need to
specify custom deleters and a desire to pass braced initializers.
3) For std::shared_ptr, additional situations where make functions may be
ill-advised include(1) classes with custom memory management and (2) systems
with memory concerns, very large objects, and std::weak_ptrs that outlive
the corresponding std::shared_ptrs.

#### Item 22: When using the pimpl idiom, define special member functions in the implementation file.
1) The Pimpl Idiom decreases the build times by reducing compilation dependencies between
class clients and class implementations.
2) For std::unique_ptr pImpl pointers, declare special member functions in the
class header, but implementation them in the implementation file. Do this even
if the default function implementations are acceptable.
3) The above advice applies to std::unique_ptr, but not to std::shared_ptr.

### Chatper 5: Rvalue References, Move Semantics, and Perfect Forwarding
#### Item 23: Understand std::move and std::forward.
1) std::move performs an unconditional cast to an rvalue. In and itself, it
doesn't move anything.
2) std::forward casts its argument to an rvalue only if that argument is bound
to an rvalue.
3) Neither std::move nor std::forward do anything at runtime.

#### Item 24: Distinguish universal references from rvalue references.
1) If a function parameter has type T&& for a deduced type T, or if an object is
declared using auto&&, the parametter or object is a universal reference.
2) If the form of the type declaration isn't precisely type&&, of if type
deduction does not occur, type&& denotes an rvalue reference.
3) Universal references correspond to rvalue references if they're initialzed
with rvalues. They correspond to lvalue references if they're initialized with
lvalues.

#### Item 25: Use std::move on rvalue references, std::forward on universal references.
1) Apply std::move to rvalue references and std::forward to universal references
the last time each is used.
2) Do the same thing for rvalue references and universal references being returned
from functions that return by value.
3) Never apply std::move and std::forward to local object if they would otherwise
be eligible for the return value optimization.

#### Item 26: Avoid overloading on universal references.
1) Overloading on universal references almost always leads to the universal
reference overload being called more frequently than expected.
2) Perfect forwarding constructors are especially problematic, because they're
typically better matches than copy constructors for non-const lvalues, and they
can hijack class calls to base class copy and move constructors.

#### Item 27: Familiarize yourself with alternatives to overloading on universal references.
1) Alternatives to the combination of universal references and overloading include
the use of distinct function names, passing parameters by lvalue-reference-to-const,
passing parameters by value, and using tag dispatch.
2) Constraining templates via std::enable_if permits the use of universal references
and overloading together, but it controls the conditions under which compilers
may use the universal reference overloads.
3) Universal references parameters often have efficiency advantages, but they
typically have usability disadvantages.

#### Item 28: Understand reference collapsing.
1) Reference collapsing occurs in four contexts: template instantation, auto type
generation, creation and use of typedef's and alias declarations, and decltype.
2) When compilers generate a reference to a reference in a reference collapsing
context, the result becomes a single reference. If ethier of the original
references is an lvalue reference, the result is an lvalue referenc. Otherwise
is't an rvalue reference.
3) Universal references are rvalue references in contexts where type deduction
distinguish lvalues from rvalues and where reference collapsing occurs.

#### Item 29: Assume that move operations are not present, not cheap, and not used.
1) Assume that move operations are not present, not cheap, and not used.
2) In code with known types or support for move semantics, there is no need for
assumptions.

#### Item 30: Familiarize yourself with perfect forwarding failure cases.
1) Perfect forwarding fails when temlate type deduction fails or when it deduces
the wrong type.
2) The kinds of arguments that lead to perfect forwarding are braced initializers,
null pointers expressed as 0 or NULL, declaration-only integeral const static data
members, template and overloaded function names, and bitfields.

### Chapter 6: Lambda Expression
#### Item 31: Avoid default capture modes.
1) Default by-reference capture can lead to dangling references.
2) Defautl by-value is suspectible to dangling pointers (especially this). and
it misleadingly suggests that lambda are self-contained.

#### Item 32: Use inti capture to move objects into closure.
1) Use C++14's init capture to move objects to closure.
2) In C++11, emulate init capture via hand-written class or std::bind.

#### Item 33: Use decltype on auto&& parameters to std::forward them.
#### Item 34: Prefer lambdas to std::bind.
1) Lambdas are more readable, more expressive, and may be more efficient than
using std::bind.
2) In C++11 only, std::bind may be useful for implementing move capture or
for binding objects with templatized function call operators.

### Chapter 7: The Concurrency API
#### Item 35: Prefer task-based programming to thread-based.
1) The std::thread API offers no direct way to get return values from asynchronously
run functions, and if those functions throw, the program is terminated.
2) Thread-based programming calls for manual management of thread exhaustion,
load-balancing, and adaptation to new platforms.
3) Task-based programming via std::async with the default launch policy handles
most of these issues for you.

#### Item 36: Specify std::launch::async if asynchronicity is essential.
1) The default launch policy for std::async permits both asynchronus and
synchronous task execution.
2) This flexibility leads to uncertainty when accessing thread_locals, implies
that the task may never execute, and affects program logic for timeout-based
wait calls.
3) Specify std::launch::async if asynchronous task execution is essential.

#### Item 37: Make std::threads unjoinable on all paths.
1) Make std::threads unjoinable on all paths.
2) join-on-destruction can lead to difficult-to-debug performance anomalies.
3) detach-on-destrution can lead to difficult-to-debug undefined behavior.
4) Declare std::thread objects last in list of data members.

#### Item 38: Be aware of varying thread handle destructor behavior.
1) Future destructors normally just destroy the future's data member.
2) The final future referring to a shared state for a non-deferred task launched
via std::async blocks until the task completes.

#### Item 39: Consider void futures for one-shot event communications.
1) For simple event communication, condvar-based design require a superfluous
mutex, impose constraints on the relative progres of detecting and reacting
tasks, and require reacting tasks to verify that the event has taken place.
2) Designs employing a flag avoid those problems, but are based on polling,
not blocking.
3) A condvar and flag can be used together, but the resulting communications
mechanism is somewhat stilted.
4) Using std:promise and futures dodges these issues, but the approach use heap
memory for shared states, and it's limited to one-shot communication.

#### Item 40: Use std::atomic for concurrency, volatile for special memory.
1) std::atomic is for data accessed from multiple threads without using mutexs,
It's a cool for writing concurrent software.
2) volatile is for memory where reads and writes should not be optimized away.
It's cool for working with special memory.

### Chapter 8: Tweaks
#### Item 40: Consider pass by value for copyable parameters that are cheap to move and always copyied.
1) For copyable, cheap-to-move parameter that are always copied, pass by value
may be nearly as efficient as pass by reference, it's easier to implement, and it
can generate less object code.
2) Copying parameters via construction may be significantly more expensive than
copying them via assignment.
3) Pass by value is subject to the slicing problem, so it's typically inappropriate
for base class paramter types.

#### Item 41: Consider emplacement instead of insertion.
1) In priciple, emplacement functions should sometimes be more efficient than
insertion counterparts, and they should never be less efficient.
2) In practice, they're most likely to be faster when (1) the value being added
is constructed in the container, not assigned; (2) the argument type(s) passed
differ from the type held by the container; and (3) the container won't reject
the value being added due to it being a duplicate.
3) Emplacement functions may perform type conversions that would be rejected by
insertion functions.
