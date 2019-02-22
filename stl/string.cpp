#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  {
    // std::string type is a fixed size, but the real data not.
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

  {
    // string == "" is equivalent string.empty()
    // yes, there are equivalent, but empty() is more clear than == ""
    // but in wstring, str == "" will not compile.
    std::string s = "Hello world!";
    s.clear();

    if (s == "") { // this way works fine too, but not work in std::wstring.
      std::cout << "string is empty" << '\n';
    }

    if (s.empty()) {
      std::cout << "string is empty" << '\n';
    }

    // std::wstring ws = ""; // illegal, won't compile.
    // if (ws == "") {
    //   std::cout << "wstring is empty" << '\n';
    // }
  }

  {
    // multiple strings share same memory palce
    std::string s1 = "hello world";
    std::string s2 = s1;

    // s1 and s2 inner pointer point to the same place ? we can see from the
    // following code, s1 and s2 do not share the same memory place.
    // in a word, two string assignment constructor will allocate the new memory
    // and copy the string.
    s2 = "good bye";
    std::cout << s1 << '\n';
    std::cout << s2 << '\n';
  }

  {
    // null-bytes in std::string
    std::string null_str("\x00");
    std::cout << null_str.length() << '\n'; // length is 0

    // what if we want to make std::string distinguish null bytes
    std::string str("");
    str.push_back('\0');
    std::cout << str.length() << '\n'; // length is 1

    // in C++14, there is a better way
    using namespace std::string_literals;
    std::string a = "\0"s; // length is 1
    std::string aa = "\0\0"s; // length is 2
    std::cout << "a length: " << a.length()
      << "\naa length: " << aa.length() << '\n';
  }

  return 0;
}
