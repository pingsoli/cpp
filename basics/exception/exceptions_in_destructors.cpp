////////////////////////////////////////////////////////////////////////////////
//
// if we throw exceptions in destructors, the program will crash.
//
// there are two ways to solve it:
// Solution 1: Destructor swallow the exception
// Solution 2: Move the exception-prone code to a different function.
//
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

class Dog {
public:
  Dog(const std::string& name) : name_(name) {
    std::cout << name_  << " is created..." << '\n';
  }

  // default destructor is noexcept, use noexcept(false) to disable it.
  ~Dog() noexcept(false) {

    // solution 1: there won't crash again.
    try {
      std::cout << name_ << " is destroyed..." << '\n';
      throw 20;
    } catch (std::exception& e) {
      // do nothing
    } catch (...) {
      // do nothing
    }
  }

  // solution 2
  void prepareToDestroy() {
    // move all the exception-prone code to here.
  }

  void bark() {
    std::cout << name_ << " is barking..." << '\n';
  }

private:
  std::string name_;
};

int main(int argc, char *argv[])
{
  try {
    Dog dog1("Alen");
    Dog dog2("Bob");

    dog1.bark();
    dog2.bark();

    // throw 20;

    // cleanup
    dog1.prepareToDestroy();
    dog2.prepareToDestroy();
  } catch (int e) {
    std::cout << e << " is caught" << '\n';
  }

  return 0;
}
