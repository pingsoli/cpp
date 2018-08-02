///////////////////////////////////////////////////////////////////////////////
// std::unique_ptr owns the object exclusively
//
// NOTE:
// Invoking constructors won't print log, maybe you need to enable
// '-fno-elide-constructors' in g++.(NOTE: it's only suit for gcc)
//
// Summary:
// 1) std::unique_ptr is exclusive-ownership smart pointer to manage resource.
// 2) std::unique_ptr like raw pointer, suited for polymorphism.
// 3) Converting std::unique_ptr to std::shared_ptr is easy.
//
// References:
// [1] https://stackoverflow.com/questions/4316727/returning-unique-ptr-from-functions
// [2] Why copy constructos is not called in this case ?
// https://stackoverflow.com/questions/1758142/why-copy-constructor-is-not-called-in-this-case
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// copy/move elision.
//
// when the criteria of elision of a copy operation are met and the object to
// be copied is designated by an lvalue, overload resolution to select the
// constructor for the copy is first performed as if the object were designated
// by an rvalue.

std::unique_ptr<int> foo() {
  std::unique_ptr<int> p(new int(42));
  return p;
}

// same as the above
std::unique_ptr<int> bar() {
  std::unique_ptr<int> p(new int(10));
  return std::move(p);
}

auto baz() {
  return std::unique_ptr<int>(new int(100));
}

int main(int argc, char** argv)
{
  {
    // std::unique_ptr is only movealbe.
    auto uptr1 = foo(); // same as std::unique_ptr<int> uptr1 = foo();
    auto uptr2 = bar(); // same as std::unique_ptr<int> uptr2 = bar();
    auto uptr3 = baz();

    std::cout << *uptr1 << '\n';
    std::cout << *uptr2 << '\n';
    std::cout << *uptr3 << '\n';
  }

  {
    // Converting std::unique_ptr to std::shard_ptr is quite easy.
    std::unique_ptr<int> upi(new int(20));
    // std::shared_ptr<int> spi = std::move(upi); // upi is null
    std::shared_ptr<int> spi(std::move(upi));

    std::cout << *spi << '\n';
  }

  return 0;
}
