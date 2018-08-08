// proxy design pattern
// what is it ?
// a proxy is class that provides a modified interface to another class.

#include <iostream>

// Q: why not add the destructor in proxy class ? such like:
//
// ~proxy() {
//   delete mPtr;
// }
//
// A: Because the proxy class's mPtr don't own the data, just point to
// the original data. If we does this like the above, double free problem will
// occur.

struct proxy {
  proxy (int& r) : mPtr(&r) {}

  proxy(const proxy& other) : mPtr(other.mPtr) {
    std::cout << "proxy copy constructor" << '\n';
  }

  // set(CMAKE_CXX_FLAGS "-fno-elide-constructors")
  // return value Optimization
  proxy(proxy&& other) : mPtr(std::move(other.mPtr)) {
    std::cout << "proxy move constructor" << '\n';
  }

  int operator=(int n) {
    if (n > 1) {
      throw "not binary digit";
    }
    return (*mPtr = n);
  }

  int *mPtr;
};

struct array {
  int mArray[10] = {0}; // supposes the array only can contains number 0 or 1.
                        // every 'bit' is initialized to zero.
  proxy operator[] (int i) {
    return proxy(mArray[i]);
  }

  void print() const {
    for (int i = 0; i < 10; ++i)
      std::cout << mArray[i] << ' ';
    std::cout << '\n';
  }
};

// array class don't change the data itself, but proxy does.

int main(int argc, char *argv[])
{
  try {
    array a;
    a[0] = 1;  // ok
    a[1] = 0;
    a[1] = a[0] = 1;
    a[2] = a[3] = 0;
    a[4] = a[5] = 1;

    // a[0] = 42; // throws exception, only contains binary number.

    a.print();
  } catch (const char *e) {
    std::cout << e << '\n';
  }

  return 0;
}
