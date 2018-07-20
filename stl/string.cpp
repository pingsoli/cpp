#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  {
    // std::string is fixed size.
    std::string str("hello");

    std::cout << "str instance size: " << sizeof(str) << '\n'; // 32
    str.append(" world");
    std::cout << "str instance size: " << sizeof(str) << '\n'; // 32
    std::cout << "str data size: " << str.size() << '\n';
  }

  {
    // string's data is refcounted ?
    // on c++11 is non-reference couting.
    // GCC make string non-reference.
  }

  return 0;
}
