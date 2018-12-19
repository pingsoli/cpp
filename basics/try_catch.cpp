
// try-catch block basic usages
// the following code is about stack unwinding and RAII.
// how to avoid memory leak ? RAII may be a approach.

#include <iostream>
#include <memory>

#define ENABLE_VIRTUAL 0

struct Base {
  Base() { std::cout << "Base constructor" << '\n';}

#if ENABLE_VIRTUAL
  virtual
#endif
  ~Base() { std::cout << "Base destructor" << '\n';}
};

struct Derived : public Base {
  Derived() { std::cout << "Derived constructor" << '\n';}

#if ENABLE_VIRTUAL
  virtual
#endif
  ~Derived() { std::cout << "Derived destructor" << '\n';}
};

int main(int argc, char *argv[])
{
  try {
    auto pb = std::make_shared<Derived>();

    // Base *b = new Derived();
    // delete b;

    throw 1;
  } catch (const int& i) {
    std::cout << i << '\n';
  } catch (const std::exception& e) {
    std::cout << e.what() << '\n';
  } catch (...) {
    std::cout << "catch all" << '\n';
  }

  return 0;
}
