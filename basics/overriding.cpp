#include <iostream>

struct Base {
  virtual void print() {
    std::cout << "base" << '\n';
  }
};

struct Derived : public Base {
  virtual void print() {
    std::cout << "derived" << '\n';
  }
};

void doit(Base& base) {
  base.print();
}

int main(int argc, char *argv[])
{
  Derived d;
  doit(d);

  return 0;
}
