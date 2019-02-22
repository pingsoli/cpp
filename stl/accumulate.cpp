#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main(int argc, char* argv[])
{
  {
    // std::vector<int> vi{1, 2, 3, 4, 5, 6, 7};
    //
    // // these two are equivalent, the default behavior plus each element.
    // auto sum = std::accumulate(begin(vi), end(vi), 0);
    // auto sum1 = std::accumulate(begin(vi), end(vi), 0, std::plus<>{});
    //
    // std::cout << sum << " " << sum1 << std::endl;
  }

  {
    // accumate the summary of a range into one value
    struct Person {
      double weight;
      int id;

      Person(int i, double w) : id(i), weight(w) { }
    };

    std::vector<Person> group = {{1, 50.0}, {2, 62.8}, {3, 70}, {4, 45.0}};
    auto totalWeight = std::accumulate(begin(group), end(group),
                              0.,
                              [](double currentWidget, const Person& p) {
                                return currentWidget + p.weight;
                              });

    std::cout << totalWeight << '\n';
  }

  return 0;
}
