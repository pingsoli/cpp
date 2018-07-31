////////////////////////////////////////////////////////////////////////////////
// best practice:
// throw by value, catch by reference.
////////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <iostream>

class MyException : public std::runtime_error {
public:
  MyException() : std::runtime_error("My Exception") {}

  virtual const char* what() throw() {
    return "My Exceoption";
  }
};

int main(int argc, char *argv[])
{
  try
  {
    throw MyException();
  }
  catch (std::runtime_error& e)  // can catch the MyException
  {
    std::cout << "runtime_error" << '\n';
    std::cout << e.what() << '\n';
  }

  return 0;
}
