///////////////////////////////////////////////////////////////////////////////
//
// std::unique_ptr owns the object exclusively
//
// NOTE
// If you can't get any output message when invoke constructors, it looks like
// these constructors are not invoked.
// maybe you need to enable '-fno-elide-constructors' of g++.
//
// References:
// [1] https://stackoverflow.com/questions/4316727/returning-unique-ptr-from-functions
// [2] Why copy constructos is not called in this case ?
// https://stackoverflow.com/questions/1758142/why-copy-constructor-is-not-called-in-this-case
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// copy/move elision.
//
// when the criteria of elision of a copy operation are met and the object to
// be copied is designated by an lvalue, overload resolution to select the
// constructor for the copy is first performed as if the object were designated
// by an rvalue.

std::unique_ptr<int> foo()
{
  std::unique_ptr<int> p(new int(42));
  return p;
}

std::unique_ptr<int> bar()
{
  std::unique_ptr<int> p(new int(10));
  return std::move(p);
}

void rvo()
{
  std::unique_ptr<int> p = foo();
  std::unique_ptr<int> q = bar();
}

///////////////////////////////////////////////////////////////////////////////
//

class X
{
private:
  int data;

public:
  X(int d = 0) : data{d}
  {
    std::cout << "default constructor" << std::endl;
  }

  int get_data() const
  {
    return data;
  }

//  X(const X& other)
//  {
//    std::cout << "copy constructor" << std::endl;
//  }

//  X& operator=(const X& other)
//  {
//    std::cout << "assignment constructor" << std::endl;
//  }

  X(X&& other)
  {
    std::cout << "move constructor" << std::endl;
  }

//  X(const X&) = delete;
//  X(X&&) = delete;
//  X& operator=(const X&) = delete;
};

X get_X(int value)
{
  return X(value); // X(X&&)
}

X create_X(int value)
{
  return value; // X(const X&)
}

void test()
{
  X x  = get_X(42); // invoke move constructor twice
  X x1 = create_X(10); // invoke copy constructor
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
//  rvo();
  test();

  return 0;
}
