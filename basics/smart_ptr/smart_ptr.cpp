////////////////////////////////////////////////////////////////////////////////
// Smart Pointer
// std::shared_ptr, std::unique_ptr
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
// smart pointer support polymorphism
struct Base {
  virtual void foo() { std::cout << "Base::foo()\n"; }
};

struct Derived : public Base {
  virtual void foo() { std::cout << "Derived::foo()\n"; }
};
////////////////////////////////////////////////////////////////////////////////
// shared_ptr reference counts
void fun(std::shared_ptr<int> sp) {
  std::cout << "fun: sp.use_count() == " << sp.use_count() << '\n';
  // It's 1 not 2, why ?
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  //////////////////////////////////////////////////////////////////////////////
  std::shared_ptr<Base> pb(new Base);
  std::shared_ptr<Base> pd(new Derived);

  pb->foo(); // Base::foo()
  pd->foo(); // Derived::foo()

  //////////////////////////////////////////////////////////////////////////////
  // check the reference count
  fun(std::make_shared<int>(5)); // reference is 1, because the move-constructs.

  std::shared_ptr<int> pi = std::make_shared<int>(4);
  fun(pi);  // reference is 2, we construct a copy.

  //////////////////////////////////////////////////////////////////////////////
  // contruct a shared_ptr from a unique_ptr
  std::unique_ptr<int> upi = std::make_unique<int>(5);
  std::shared_ptr<int> spi(std::move(upi));

  std::cout << *spi << '\n'; // 5
  std::cout << spi.use_count() << '\n'; // 1
  // now upi is dangling smart pointer.
  //////////////////////////////////////////////////////////////////////////////

  {
    // custom the deleter for std::shared_ptr and std::unique_ptr
    // the difference: the deleter is a part of std::unique_ptr,
    // but is not part of std::shared_ptr.
    // specify the deleter doesn't change the size of a std::shared_ptr object.
  }


  return 0;
}
