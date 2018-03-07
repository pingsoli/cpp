///////////////////////////////////////////////////////////////////////////////
//
// Item 25: Consider support for a non-throwing swap
//
// 1) Provide a swap memeber function when std::swap would be inefficient for
// your type. Make sure your swap doesn't throw exepctions.
//
// 2) If you offer a member swap, also offer a non-member swap that calls the
// member. For classes (not templates), specialize std::swap, too.
//
// 3) When calling swap, employ a using ceclaration for std::swap, then call
// swap without namespace qualification.
//
// 4) It's fine to totally specialize std templates for user-defined types, but
// never try to add something completely new to std.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

void print(const std::vector<int>& v, const std::string& name)
{
  std::cout << "name: " << name << std::endl;

  std::for_each(v.begin(), v.end(),
      [] (const int& e) {
        std::cout << e << ' ';
      });

  std::cout << '\n' << std::endl;
}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // swap vector array

  std::vector<int> v1 = { 1, 2, 3, 4, 5 };
  std::vector<int> v2 = { 6, 7, 8, 9, 0 };

  std::swap(v1, v2);

  print(v1, "v1");
  print(v2, "v2");

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
