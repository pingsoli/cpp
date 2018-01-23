# C++ Rvalue References Explained

## Introduction

Rvalue references solve at least two problems:<br>  
1) Implementing move semantics<br>
2) Perfect forwarding<br> 

```
  int a = 42;
  int b = 43;

  // a and b are both l-values
  a = b;  // ok
  b = a;  // ok
  a = a * b;  // ok

  // a * b is an rvalue
  int c = a * b;  // ok, rvalue on right hand side of assignment
  //a * b = 42;  // error, rvalue on left hand size of assignment 
  // main.cpp|15 col 9| error: lvalue required as left operand of assignment

  // lvalues
  //
  int i = 42;
  i = 43;  // ok, i is an lvalue
  int* p = &i; // ok , i is an lvalue

  int& foo();
  foo() = 42; // ok, foo() is an lvalue
  int* p1 = &foo(); // ok, foo() is an lvalue

  // rvalues
  //
  int foobar();
  int j = 0;
  j = foobar();  // ok, foobar() is an rvalue
  int* p2 = &foobar();  // error, cannot take the address of an rvalue
  j = 42; // ok, 42 is an rvalue
```

## Move Sematics

```
X& X::operator=(X const & rhs)
{
  // [...]
  // Make a clone of what rhs.m_pResource refers to.
  // Destruct the resource that m_pResource refers to.
  // Attach the clone to m_pResource.
  // [...]
}

X foo();
X x;

// perhaps use x in various ways.
x = foo();

```
The last line above:<br>
1) clones the resource from the temporary returned by foo. <br>
2) destructs the resource held by x and replace it with clone.<br>
3) destructs the temporary and thereby releases its resouces<br>

Move semantics with C++ 11, this conditional behavior can be achieved
via an overloaad:

```
X& X::operator=(<mystery type> rhs)
{
  // [...]
  // swap this->m_pResource and rhs.m_pResource
  // [...]
}
```
## Rvalue References
```
void foo(X& x);  // lvalue reference overload
void foo(X&& x);  // rvalue reference overload

X x;
X foobar();

foo(x); // argument is lvalue: calls foo(X&)
foo(foobar());  // argument is rvalue: call foo(X&&)
```
Rvalue references allow a function to branch at compile time 
(via overload resolution) on the condition "Am I being called on an 
lvalue or an rvalue?"<br>

```
X& X::operator=(X const & rhs); // classical implementation
X& X::operator=(X&& rhs)
{
  // Move semantics: exchange content with this and rhs
  return *this;
}
```
## Forcing Move Semantics
```
X& X::operator=(X&& rhs)
{
  // perform a cleanup that take care of those part of
  // destructor that have side effects. Be sure to leave the 
  // object in a destructible and assignable state.

  // Move semantics: exchange content with this and rhs

  return *this;
}
```

## Is an Rvalue Reference an Rvalue?
Things that declared as rvalue reference can be lvalues or rvalues.
The distinguishing criterion is: if it has a name, then it is an 
lvalue. Otherwise, it is an rvalue.

```
void foo(X&& x)
{
  X anotherX = x;  // Calls X(X const & rhs)
}

X&& goo();
X x = goo();  // Calls X(X&& rhs) because the thing on the 
              // right hand has no name
```

std::move() make lvalue be rvalue.

```
Base(Base const &rhs);  // non-move semantics
Base(Base&& rhs);       // move semantics


Derived(Derived const &rhs)
  : Base(rhs)
{
  // Derived-specific stuff
}

Derived(Derived&& rhs)
  : Base(rhs)  // Wrong: rhs is an lvalue
{
  // Derived-specific stuff
}

Derived(Derived&& rhs)
  : Base(std::move(rhs))  // Good, calls Base(Base&& rhs)
{
  // Derived-sepcific stuff
}
```
## Perfect Forwarding: The Problem

```
template <typename T, typename Arg>
shared_ptr<T> factory(Arg arg)
{
  return shared_ptr<T>(new T(arg));
}

// reference
template <typename T, typename Arg>
shared_ptr<T> factory(Arg& arg)
{
  return shared_ptr<T>(new T(arg));
}

// But it cannot deal with rvalue
factory<X>(hoo());  // error if hoo returns by value
factory<X>(41);  // error

// next solution, but it is not perfect
template <typename T, typename Arg>
shared_ptr<T> factory(Arg const & arg)
{
  return shared_ptr<T>(new T(arg));
}

1) sereral arguments, you would have to provide overloads for all
   combinations of non-const and const reference of the vaious 
   arguments
2) it blocks out move semantics.
```

## Perfect Forwarding: The Solution

A& &   becomes A&<br>
A& &&  becomes A&<br>
A&& &  becomes A&<br>
A&& && becomes A&&<br>

```
template <typename T, typename Arg>
shared_ptr<T> factory(Arg&& arg)
{
  return shared_ptr<T>(new T(std::forward<Arg>(arg)));
}

// Where std::forward is defined as follows:
template <class S>
S&& forward(typename remove_reference<S>::type& a) noexcept
{
  return static_cast<S&&>(a);
}
```

## References
[1] http://www.artima.com/cppsource/rvalue.html<br>
[2] http://thbecker.net/articles/rvalue_references/section_1.html<br>
[3] https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers<br>
