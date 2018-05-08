////////////////////////////////////////////////////////////////////////////////
//
// Empty Base Optimization
//
// What is empty-base-optimization ?
// the size of any object or member subobject is required to be at least 1 even
// if the type is an empty class type(that is, a class or struct has non-staic
// data members), in order to be able to guarantee that
// the addresses of distinct objects of the same type are always distinct.
//
// key: C++ requires empty classes to have non-zero size to ensure object
// identity.
//
// Why need empty class ?
// template (meta-)programming: for instance, iterator tags are implemented as
// empty classes.
//
// C++20 [[no_unique_address]] enable the empty base class optimization.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct Base {};

struct Derived1 : Base {
  int i;
};

// Empty base optimization is prohibited if the empty base classes is also the
// type or the base of the first non-static data member, since the two base
// subobject of the same type are required to have different address within the
// object representation of the most derived type.
//
// NOTE: first non-static data member.
struct Derived2 : Base {
  Base c;  // Base, occupies 1 byte, followed by padding for i
  int i;
};

struct Derived3 : Base {
  Derived1 c;  // derived from Base, occupies sizeof(int) bytes
  int i;
};

int main(int argc, char** argv)
{
  std::cout << sizeof(Base) << std::endl;     // 1 bytes

  // empty base optimization applies
  std::cout << sizeof(Derived1) << std::endl; // 4 bytes

  // empty base optimization does not apply
  // base occupies 1 byte, Base member occupies 1 byte
  // followed by 2 bytes of padding to satisfy int alignment requirements
  std::cout << sizeof(Derived2) << std::endl;  // 8 bytes

  // empty base optimization does not apply
  // base takes up at least 1 byte plus the padding
  // to satisfy alignment requirement of the first member (whose
  // alignment is the same as int)
  std::cout << sizeof(Derived3) << std::endl;  // 12 bytes

  return 0;
}
