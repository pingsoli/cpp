// auto keyword
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
  {
    int x1; // potentially unintialized.
    // auto x2; // error! initializer required.
    auto x3 = 0; // fine. x's value is well-defined.
  }

  {
    // check and output type when using auto keyword.
    auto x = 4;
    auto y = 3.37;
    auto ptr = &x;

    std::cout << typeid(x).name() << '\n'
              << typeid(y).name() << '\n'
              << typeid(ptr).name() << '\n';
  }

  {
    // avoid long initialization
    std::vector<int> vi{ 1, 2, 3, 4, 5, 6 };

    for (auto it = vi.begin(); it != vi.end(); ++it)
      std::cout << *it;
    std::cout << '\n';
  }

  return 0;
}
