// noexcept specification indicate the function will not throw any exception.
// the compiler will optimize the code accorindg `noexcept`.
// but if you throw a exception from a noexcept function, std::terminate() will
// be triggered.
//
// Summary:
// 1) use noexcpet if you make sure the function won't throw any exceptions.
#include <exception>
#include <iostream>

class MyClass
{
public:
  MyClass() { std::cout << "Constructor" << '\n'; }
  ~MyClass() { std::cout << "Destructor" << '\n';}

  // throw exception inner the noexcept specification.
  // if we pass 0.0 as y, that will trigger std::terminate(), because we violate
  // the exception specification.
  //
  // The compiler will not check the `noexcept` specification at compile time.
  double compute(double x, double y) noexcept { // Promises to not throw any exception
    if (y == 0)
      throw std::logic_error("the denominator should not be zero"); // Violates the exception specification.
    return x / y;
  }
};

int main(int argc, char *argv[])
{
  try {
    MyClass my;
    double result;
    result = my.compute(1.0, 0.0); // std::terminate() will be triggered

  } catch (std::exception& e) {
    std::cout << "Catch the exception: " << e.what() << '\n';
  } catch (...) {
    std::cout << "Unknowed exception" << '\n';
  }

  return 0;
}
