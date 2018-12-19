#include <iostream>

struct test {
  int i;

  test() : i(3) {}

  void f(int v) const {
    // this->i = v; // compile error: this is a pointer to const
    const_cast<test*>(this)->i = v; // another way to add `mutable` to variable i.
  }
};

int main(int argc, char *argv[])
{
  {
    int i = 3;
    const int& rci = i;
    // rci = 4; // error
    const_cast<int&>(rci) = 4; // ok
  }

  {
    test t;
    t.f(4);
  }

  {
    const int j = 3;
    int* pj = const_cast<int*>(&j);
    *pj = 4; // undefined behavior, maybe it's still 3.

    std::cout << j << '\n';
  }

  return 0;
}
