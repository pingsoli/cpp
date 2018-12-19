#include <iostream>
#include <vector>

struct B {
  int m = 0;
  void hello() const {
    std::cout << "hello world, this is B" << '\n';
  }
};

struct D : public B {
  void hello() const {
    std::cout << "hello world, this id D" << '\n';
  }
};

enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };

int main(int argc, char *argv[])
{
  {
    // 1: initialization conversion
    int n = static_cast<int>(3.14);
    std::cout << "n = " << n << '\n';
    std::vector<int> v = static_cast<std::vector<int>>(10);
    std::cout << "v.size() = " << v.size() << '\n';
  }

  {
    // 2: static downcast
    D d;
    B& br = d;
    br.hello();
    D& another_d = static_cast<D&>(br);
    another_d.hello();
  }

  {
    // scoped enum to int or float
    E e = E::ONE;
    int one = static_cast<int>(e);
    std::cout << one << '\n';
  }

  {
    // int to enum, enum to another enum
    int one = 1;
    E e = E::ONE;
    E e2 = static_cast<E>(one);
    EU eu = static_cast<EU>(e2);
  }

  {
    // void* to any type
  }

  return 0;
}
