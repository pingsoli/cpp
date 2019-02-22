// [x1, x2, x3, ..., xn]
//        | f
//        v
// [f(x1), f(x2), ..., f(xn)]
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main(int argc, char *argv[])
{
  {
    // [x1, x2, x3, ..., xn]
    //        | f
    //        v
    // [f(x1), f(x2), ..., f(xn)]
    std::map<int, std::string> m = {{1, "foo"}, {42, "bar"}, {7, "baz"}};
    std::vector<int> keys;

    using map_iterator = std::map<int, std::string>::iterator;
    auto getFirst = [&m] (const decltype(m)::value_type& pair) { return pair.first; };
    std::transform(m.begin(), m.end(), std::back_inserter(keys), getFirst);

    // print all keys
    std::for_each(keys.begin(), keys.end(), [] (const decltype(keys)::value_type& v) {
        std::cout << v << '\n';
        });
  }

  {
    // // [x1, x2, ..., xn] && [y1, y2, ..., y3]
    // //                || f
    // //                VV
    // // [f(x1, y1), f(x2, y2), ..., f(xn, yn)]
    //
    // std::vector<int> numbers1 = {1, 2, 3, 4};
    // std::vector<int> numbers2 = {5, 6, 7, 7};
    // std::vector<int> results;
    //
    // std::transform(numbers1.begin(),
    //                numbers1.end(),
    //                numbers2.begin(),
    //                std::back_inserter(results),
    //                [] (int i, int j) { return i + j; });
    //
    // std::for_each(results.begin(),
    //               results.end(),
    //               [] (const int& v) { std::cout << v << '\n'; });
  }

  return 0;
}
