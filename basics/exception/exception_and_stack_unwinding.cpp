////////////////////////////////////////////////////////////////////////////////
// more detail about the exception stack unwinding.
//
// references
// [1] https://msdn.microsoft.com/en-us/library/hh254939.aspx
// [2] https://www.geeksforgeeks.org/stack-unwinding-in-c/
////////////////////////////////////////////////////////////////////////////////

// What is stack unwinding ?
// The process of removing function entries from function call stack at run time.
//
// If a matching catch handler is found, the exception object will be
// intitialized (basic two ways: pass-by-value or pass-by-reference).
// After initialization, the process of unwinding the stack begins.
// This involves the destruction of all automatic objects that were fully
// constructed.
// Destruction occurs in reverse order of construct that is not a catch handler.

#include <iostream>
#include <exception>
#include <string>

class Test
{
public:
  Test(const std::string& name) :
    name_(name), i(0) {
    std::cout << "Constructor called" << '\n';
  }

  Test(const Test& other) :
    name_(other.name_), i(other.i) {
    std::cout << "Copy constructor called" << '\n';
  }

  ~Test() {
    std::cout << "Destructor called" << '\n';
  }

private:
  std::string name_;
  int i;
};

// A() -> B() -> C()
// C throws exception
void C(Test t) {
  std::cout << "Entering fucntion C" << '\n';
  throw std::runtime_error("thrown from C function");
  std::cout << "Exciting function C" << '\n';
}

void B(Test t) {
  std::cout << "Entering fucntion B" << '\n';
  C(t);
  std::cout << "Exciting function B" << '\n';
}

void A(Test t) {
  std::cout << "Entering fucntion A" << '\n';
  B(t);
  std::cout << "Exciting function A" << '\n';
}

int main(int argc, char *argv[])
{
  try
  {
    Test t("test");
    A(t);
  }
  catch (std::exception& e)
  {
    std::cout << "Catched the exception, the message is: " << e.what() << '\n';
  }

  std::cout << "Exiting main function" << '\n';
  return 0;
}

// What happened when stack unwinding in above code?
// when calling A(t) throws exceptions, its entry is removed from the function
// stack(because its A() doesn't contain exception handler for the thrown
// exception), then next entry in call stack is looked for exception handler.
// the next entry is B(). Since B() also doesn't have handler, its entry is also
// removed from function call stack. the next entry in function call stack is
// C(). since C() also doesn't have handler, its entry is also removed from
// function call stack. now it goes back to main function, and the exception
// handler is found and matched, then the catch block is executed.
//
// when removing entry from function call stack, the automatic variable will be
// destructed, so we can see the output from console.
// note that the following lines inside A(), B() and C() are not executed at all.

// Output:
// Constructor called
// Copy constructor called
// Entering fucntion A
// Copy constructor called
// Entering fucntion B
// Copy constructor called
// Entering fucntion C
// Destructor called
// Destructor called
// Destructor called
// Destructor called
// Catched the exception, the message is: thrown from C function
// Exiting main function
