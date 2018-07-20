#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

int main(int argc, char *argv[])
{
  {
    // using IntVector     = std::vector<int>;
    // using IterType      = IntVector::iterator;
    // using ConstIterType = IntVector::const_iterator;
    //
    // IntVector vi = {1, 2, 3, 4, 5, 6};
    // IterType iter(vi.begin());
    // ConstIterType citer(vi.cbegin() + 2);
    //
    // // convert const_iterator to iterator, make iterator point the place of const_iterator
    // // std::advance(iter, std::distance(iter, citer));  // illegal
    // std::advance(iter, std::distance<ConstIterType>(iter, citer));
    //
    // std::cout << *iter << '\n';
    //
    // for (auto it = vi.begin(); it != vi.end(); ++it)
    //   std::cout << *it << ' ';
    // std::cout << '\n';
  }

  {
    // std::vector<int> vi;
    // vi.reserve(5);
    //
    // for (int i = 0; i < 5; ++i) {
    //   vi.push_back(i);
    // }
    //
    // std::vector<int>::reverse_iterator ri =  // make ri point to 3
    //   std::find(vi.rbegin(), vi.rend(), 3);
    //
    // // convert reverse_iterator to iterator
    // std::vector<int>::iterator i(ri.base());
    // std::cout << "reverse iterator: " << *ri << ", iterator: " << *i << '\n';
    //
    // // erase
    // vi.erase(--ri.base());
    // // vi.erase((++ri).base());
    // for (auto it = vi.begin(); it != vi.end(); ++it)
    //   std::cout << *it << ' ';
    // std::cout << '\n';
  }

  {
    // read single character in file stream every time.
    std::ifstream inputFile("Makefile");
    std::string fileData((std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>());
    std::cout << fileData << '\n';

    // conclude
    // if you're only interested in the raw character, use an istreambuf_iterator
    // if you're interested in the formatted input, use istream_iterator.
  }

  return 0;
}
