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

  pi.reset();

  // check the std::shared_ptr is dangle ?
  std::weak_ptr<int> wi(pi);
  if (!wi.expired()) {
    std::cout << *pi << '\n';
  }

  // get std::shared_ptr from std::weak_ptr
  auto npi = wi.lock();
  if (npi)
    std::cout << *npi << '\n';

  // same as before
  if (pi) {
    std::cout << *pi << '\n';
  }

  return 0;
}
