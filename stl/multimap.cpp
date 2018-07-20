// every item is key-value pair.
// multimap allows the key has same value.

#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>

int main(int argc, char *argv[])
{
  {
    // basic usage
    std::multimap<char, int> mapOfPos = {
      // "this is it"
      //  0123456789
      {'t', 0},
      {'h', 1},
      {'i', 2},
      {'s', 3},
      {'i', 5},
      {'s', 6},
      {'i', 8}
    };

    // insert an element in map
    mapOfPos.insert(std::pair<char, int>('t', 9));

    using ele_type = std::pair<char, int>;
    // insert same element
    mapOfPos.insert(ele_type('t', 9));

    // iterate over the multimap
    using MultimapIter = std::multimap<char, int>::iterator;
    for (MultimapIter it = mapOfPos.begin();
        it != mapOfPos.end(); ++it)
      std::cout << it->first << " :: " << it->second << '\n';

    std::cout << "************************" << '\n';

    // iterate over the multimap using range based for loop
    for (std::pair<char, int> e : mapOfPos)
      std::cout << e.first << " :: " << e.second << '\n';
  }

  {
    // get the groups of data from multimap
    std::multimap<std::string, int> groups = {
      {"Group1", 1},
      {"Group1", 2},
      {"Group1", 3},

      {"Group2", 10},
      {"Group2", 10},
      {"Group2", 10}
    };

    groups.insert(std::make_pair("Group1", 4));

    struct Summer {
      typedef std::multimap<std::string, int>::value_type const& s_type;
      int operator()(int x, s_type y) { return x + y.second; }
    };

    auto range = groups.equal_range("Group1");
    int total = std::accumulate(range.first, range.second, 0, Summer());
    std::cout << "the total number is: " << total << '\n';
  }

  return 0;
}
