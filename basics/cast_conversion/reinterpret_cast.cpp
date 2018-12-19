#include <iostream>
#include <cstdint>
#include <cassert>

int main(int argc, char *argv[])
{
  int i = 7;
  {
    // pointer to integer and back
    std::uintptr_t v1 = reinterpret_cast<std::uintptr_t>(&i);
    // std::uintptr_t v2 = static_cast<std::uintptr_t>(&i);

    int *p1 = reinterpret_cast<int*>(v1);
    assert(p1 == &i);
  }
  return 0;
}
