// push_back, emplace_back and emplace, insert
//
// insert to specific posotion.
// insert(pos, val...) and emplace(pos, val...)
//
// insert to the back of the container.
// push_back(val) and emlace_back(val)
//
// std::vector::insert copies or moves the elements into the container by calling
// copy constructor or move constructor. (call the copy/move constructor)
// the same as std::vector::push_back.
//
// std::vector::emplace elements are constructed in-place, no copy or move
// operations are performed. (construct them inside of the vector)

#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  std::vector<std::string> vs;

  vs.push_back("hello"); // construct a temporary std::string from the string literal
                         // copy or move to the vector.
  vs.emplace_back("world"); // construct string directly inner the vector

  vs.emplace(vs.begin(), "test");
  vs.insert(vs.begin(),  "pingsoli");

  for (auto it = vs.begin(); it != vs.end(); ++it)
    std::cout << *it << '\n';

  return 0;
}
