// virtual inheritance
//   A
//  / \
// B   C
//  \ /
//   D
//
// diamond problem (without virtual inheritance)
// A   A
// |   |
// B   C
//  \ /
//   D
//
// virtual inheritance means that there will be only 1 instance of the base A
// class not 2.
//
// class B: [A fields | B fields]
//           ^---------- pointer to A
//
// class C: [A fields | C fields]
//           ^---------- pointer to A
//
// class D: [A fields | B fields | C fields | D fields]
//           ^---------- pointer to B::A
//           ^---------------- pointer to C::A
//

#include <iostream>

struct A { public: void print(){ std::cout << "A" << '\n';} };
struct B : virtual public A { public: void print(){ std::cout << "B" << '\n';}};
struct C : virtual public A { public: void print(){ std::cout << "C" << '\n';}};
struct D : public B, C { public: void print(){ std::cout << "D" << '\n';}};

int main(int argc, char *argv[])
{
  A *a = new D();
  a->print();

  std::cout << "A class size: " << sizeof(A) << '\n'; // 1
  std::cout << "B class size: " << sizeof(B) << '\n'; // 8
  std::cout << "C class size: " << sizeof(C) << '\n'; // 8
  std::cout << "D class size: " << sizeof(D) << '\n'; // 16

  return 0;
}
