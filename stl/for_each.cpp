#include <algorithm>
#include <vector>
#include <iostream>

// Encapsulate std::for_each ourself
namespace ranges
{
  template<typename Range, typename Function>
  Function for_each(Range& range, Function f)
  {
    return std::for_each(begin(range), end(range), f);
  }
}

int main(int argc, char *argv[])
{
  std::vector<int> vi = {-1, 0, 1};

  // Don't modify the element of container
  auto displayAsInstruction = [] (int number) {
    if (number > 0)
      std::cout << '+' << number << '\n';
    else if (number < 0)
      std::cout << number << '\n';
    else if (number == 0)
      std::cout << "nop" << '\n';
  };

  // Modify the element of container using reference
  auto doubler = [] (int& number) {
    number *= 2;
  };

  auto displayAllElements = [] (int number) {
    std::cout << number << '\n';
  };

  std::for_each(vi.begin(), vi.end(), displayAsInstruction);
  std::for_each(vi.begin(), vi.end(), doubler);
  std::for_each(vi.begin(), vi.end(), displayAllElements);

  // more concise way to achive the above code
  ranges::for_each(vi, displayAsInstruction);
  ranges::for_each(vi, doubler);
  ranges::for_each(vi ,displayAllElements);

  return 0;
}
