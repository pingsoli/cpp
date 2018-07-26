#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main(int argc, char *argv[])
{
  std::vector<int> from_vector;
  for (int i = 0; i < 10; ++i)
    from_vector.push_back(i);

  std::vector<int> to_vector;
  std::copy_if(from_vector.begin(), from_vector.end(),
      std::back_inserter(to_vector),
      // to_vector.begin(), // what's happened here ?
      [] (const int i) { return (i % 2 == 0); });

  std::copy(to_vector.begin(), to_vector.end(),
      std::ostream_iterator<int>(std::cout, " "));

  return 0;
}
