#include <iostream>
#include <functional>

struct X
{
  int x;

  int& easy() { return x; }
  int& get()  { return x; }
  const int& get() const { return x; }
};

int main(int argc, char *argv[])
{
  auto a = std::mem_fn(&X::easy);
  auto b = std::mem_fn<int& ()>(&X::get);
  auto c = [] (X& x) { return x.get(); };

  X x = {33};
  std::cout << "a() = " << a(x) << '\n';
  std::cout << "b() = " << b(x) << '\n';
  std::cout << "c() = " << c(x) << '\n';

  return 0;
}
