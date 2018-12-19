#include <iostream>

struct Base {
  virtual ~Base() {}
  virtual void name() { std::cout << "Base" << '\n'; }
};

struct Derived : public Base {
  virtual ~Derived() {}
  virtual void name() { std::cout << "Derived" << '\n'; }
};

int main(int argc, char *argv[])
{
  {
    Base* base = new Base();
    if (Derived* d = static_cast<Derived*>(base)) {
      d->name(); // is it safe when base class without name() ?
    }
  }

  {
    Base* pd = new Derived;
    if (Derived *d = static_cast<Derived*>(pd)) {
      d->name();
    }
  }

  return 0;
}
