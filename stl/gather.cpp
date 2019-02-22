// gather the given index elements of the container
// gather implementation is derived from Sean Parent

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

template<typename BiIt, typename UnPred>
auto gather(BiIt first, BiIt last, BiIt position, UnPred p) -> std::pair<BiIt, BiIt>
{
  using value_type = typename std::iterator_traits<BiIt>::value_type;
  return { std::stable_partition(first, position, [&] (const value_type& x) { return !p(x); }),
           std::stable_partition(position, last, p)};
}

int main(int argc, char *argv[])
{

  {
    std::vector<int> idxs = {1, 3, 5, 8}; // indexs that we want to gather
                            // index: 0    1    2    3    4    5    6    7    8
    std::vector<std::string> data = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};

    int idx = 0;
    auto fetchElement = [&idxs, &idx] (const decltype(data)::value_type& v) {
      return (std::find(idxs.begin(), idxs.end(), idx++) != idxs.end());
    };

    auto result = gather(data.begin(), data.end(),
        data.begin() + (data.size() / 2),
        fetchElement);

    std::for_each(result.first, result.second, [] (const auto& v) {
        std::cout << v << '\n';
        });

    std::cout << "Print all data..." << '\n';
    std::for_each(data.begin(), data.end(),
        [] (const decltype(data)::value_type& v) {
          std::cout << v << '\n';
        });
  }

  return 0;
}
