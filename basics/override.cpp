#include <iostream>
#include <memory>

class Base {
public:
  virtual void mf1() const {
    std::cout << "Base::void mf1()" << '\n';
  }

  virtual void mf2(int x) {
    std::cout << "Base::void mf2(int x)" << '\n';
  }

  virtual void mf3() & {
    std::cout << "Base::void mf3() &" << '\n';
  }

  virtual void mf4() const {
    std::cout << "Base::void mf4() const" << '\n';
  }
};

class Derived : public Base {
public:
  virtual void mf1() const override {
    std::cout << "Derived::void mf1()" << '\n';
  }

  virtual void mf2(int x) override {
    std::cout << "Derived::void mf2(unsigned int x)" << '\n';
  }

  virtual void mf3() & override {
    std::cout << "Derived::void mf3() &&" << '\n';
  }

  void mf4() const override { // adding "virtual" is ok, but not necessary.
    std::cout << "Derived::void mf4() const" << '\n';
  }
};

int main(int argc, char *argv[])
{
  std::unique_ptr<Base> pb = std::make_unique<Derived>();

  pb->mf1();
  pb->mf2(1);
  pb->mf3();
  pb->mf4();

  return 0;
}
