// std::copy()
// std::move()
// std::copy_backward()

#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
  // Copy
  {
    // std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // std::vector<int> another_container(10);
    //
    // // Make sure new container has more or equal elements than old one
    // std::copy(numbers.begin(), numbers.end(), another_container.begin());
    //
    // for(int v : another_container) std::cout << v << ' ';
  }

  // Move
  {
    // std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // std::vector<int> another_container(10);
    //
    // std::move(numbers.begin(), numbers.end(), another_container.begin());
    //
    // for (int v : numbers) std::cout << v << ' ';
    // std::cout << '\n';
    // for (int v : another_container) std::cout << v << ' ';
  }

  // std::backward solve overlap
  {
    // std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //
    // // NOTE: the third arguments is the last iterator of output range
    // std::copy_backward(numbers.begin(), numbers.begin() + 5, numbers.begin() + 8);
    // for (int n : numbers) std::cout << n << ' ';
  }

  return 0;
}
