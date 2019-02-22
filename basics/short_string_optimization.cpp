// Short String Optimization(SSO)
// Avoid heap allocation of std::string when storing small string, the modern
// compiler will use SSO mechanism to get better performance, there will be no
// heap allocation, instead of stack allocation.

#include <string>
#include <new>
#include <cstdio>
#include <cstdlib>
#include <iostream>

// Memory layout of std::string
//
// the simplest implementation(without SSO mechanism)
// class string
// {
//   char* _begin;
//   size_t _size;
//   size_t _capacity;
//   // ...
// };
//
// Add Short-String-Optimization(Implemented by ourself, not standard libraries)
// class string
// {
//   union Buffer
//   {
//     char* _begin;
//     char[16] _local;
//   };
//
//   Buffer buffer;
//   size_t _size;
//   size_t _capacity;
// }
//
// What the mechanism of short-string-optimization ?
// std::string stores the size and capacity, it's simple to know the stored
// string size and decide whether use SSO mechanism.

size_t allocated = 0;

void* operator new(size_t sz) {
  void* p = std::malloc(sz);
  allocated += sz;
  return p;
}

void operator delete(void* p) noexcept {
  return std::free(p);
}

int main(int argc, char *argv[])
{

  // string inner consistance
  {
    allocated = 0;
    // std::string s{"hello world"}; // heap size is 0
    // std::string s{"123456789012345"}; // heap size is 0
    std::string s{"1234567890123456"}; // heap size is 17
    std::cout << "stack space = " << sizeof(s) << ", heap space = " << allocated
      << ", capacity = " << s.capacity() << '\n';
  }

  return 0;
}
