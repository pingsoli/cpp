#include <vector>
#include <iostream>
#include <algorithm>

struct S
{
  int number;
  char name;

  bool operator<(const S& s) const { return number < s.number; }
  // constexpr bool oprator(const S& s) { return number < s.number; } // illegal
};

int main(int argc, char *argv[])
{
  std::vector<S> vs = {{1, 'a'}, {2, 'b'}, {2, 'c'}, {2, 'd'}, {3, 'f'}, {4, 'g'}};
  S value = {2, '?'};

  auto range = std::equal_range(vs.begin(), vs.end(), value);
  for (auto it = range.first; it != range.second; ++it)
    std::cout << it->number << " : " << it->name << '\n';

  struct Comp {
    bool operator()(int i, const S& s) const { return i < s.number; }
    bool operator()(const S& s, int i) const { return s.number < i; }
  };

  auto range2 = std::equal_range(vs.begin(), vs.end(), 2, Comp{});

  for (auto it = range2.first; it != range.second; ++it)
    std::cout << it->number << " : " << it->name << '\n';

  return 0;
}
