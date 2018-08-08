////////////////////////////////////////////////////////////////////////////////
// weak_ptr has no dereference operation.
// It's designed to check the smart_ptr whether is dangle ?
// but there cause the new problem, race condition.
//
// In addition, std::weak_ptr is used to break circular reference of std::shared_ptr
//
// Potential use cases for std::weak_ptr include caching, observer list, and the
// prevention of std::shared_ptr cycles.
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <iostream>

int main(int argc, char *argv[])
{
  std::shared_ptr<int> pi(new int(10));

  // pi.reset(); // clear the shared_ptr, the use_count will be zero.

  // create weak pointer from shared_ptr.
  // std::weak_ptr<int> wi(pi); // same as the following
  std::weak_ptr<int> wi = pi;

  // only check the shared_ptr whether is present.
  if (!wi.expired()) {
    std::cout << *pi << '\n';
  }

  // get std::shared_ptr from std::weak_ptr. the weak pointer doesn't have *
  // and -> operators overload, so you cannot dereference underlying pointer
  // before converting to shared_ptr(via lock())
  if (auto observe = wi.lock()) {
    std::cout << *observe << '\n';
  }

  // get the use count of shared_ptr, return 0 if destoryed.
  std::cout << "shared_ptr use count: "
            << wi.use_count() << '\n';

  // same as before
  if (pi) {
    std::cout << *pi << '\n';
  }

  return 0;
}
