#include <iostream>

class UPint
{
public:
  UPint() = default;
  UPint(int val) : value(val) { }
  unsigned int value;
};

const UPint operator+(const UPint& lhs, const UPint& rhs) {
  return UPint(lhs.value + rhs.value);
}

const UPint operator+(int x, const UPint& rhs) {
  std::cout << "operator+(int, const UPint&)" << '\n';
  return UPint(x + rhs.value);
}

const UPint operator+(const UPint& lhs, int x) {
  std::cout << "operator+(const UPint&, int)" << '\n';
  return UPint(lhs.value + x);
}

int main(int argc, char *argv[])
{
  UPint up1, up2, up3;

  up3 = up1 + up2;
  up3 = 1 + up2; // there are so many thing compiler do in the background.
  up3 = up1 + 2; // implicit convertion a integer to temporary UPint instance.

  // how to avoid the implicit conversion, we can overload the function
  // operator+(cosnt UPint& lhs, int)
  // operator+(int, const UPint& rhs)

  // if we want to avoid implicit conversion, we must point it out using explicit keyword.

  return 0;
}
