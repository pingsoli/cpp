#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
  std::unique_ptr<int> pi = std::make_unique<int>(1);

  // Prefer unique_ptr than shared_ptr, if you don't know the object whether is
  // shared.

  std::cout << *pi << '\n';

  // convert unique_ptr to shared_ptr
  // std::shared_ptr<int> psi = std::move(pi); // same as the bellow
  std::shared_ptr<int> psi(std::move(pi));
  std::cout << *psi << '\n';

  // converting shared_ptr to unique_ptr is not allowed.

  // best practice
  // void sink(std::unique_ptr<widget>, std::unique_ptr<gadget>);
  //
  // // exception-safe
  // sink(std::make_unique<widget>(), make_unique<gadget>());

  return 0;
}
