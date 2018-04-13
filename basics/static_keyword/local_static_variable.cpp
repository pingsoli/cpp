#include <iostream>

// static variable can be initialized only once
// the outside code cannot use local static variable
void func() {
  static int n;
  std::cout << n++ << std::endl;
}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  // local static variable
  for (int i = 0; i < 5; ++i) {
    func();
  }
  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
