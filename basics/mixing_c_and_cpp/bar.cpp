#include <iostream>

extern "C" void bar(int i) {
  std::cout << "void bar(int i)\n";
}

// void C::bar(int i) {
//   std::cout << "void C::bar(int i)" << std::endl;
// }
//
// // wrapper function
// extern "C" void call_c_bar(C* p, int i) {
//   p->bar(i);
// }
