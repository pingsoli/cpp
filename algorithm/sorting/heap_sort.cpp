////////////////////////////////////////////////////////////////////////////////
//
// heap sort - max heap bottom-up solution
// from https://gist.github.com/karl-von-moor/2622383
//
// heap sort is stable.
//
// Time complexity
// O (n log n)
//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iterator>
#include <vector>

template <typename Container>
void heap(Container& A, std::size_t i, std::size_t delim)
{
  std::size_t left = 2*i+1, right = 2*i+2;
  if (right >= delim) return;

  if ((A[left] > A[right] && A[left] > A[i]))
  {
    std::swap(A[i], A[left]);
    heap(A, left, delim);
  }
  else if (A[right] > A[i])
  {
    std::swap(A[i], A[right]);
    heap(A, right, delim);
  }
}

template <typename Container>
void heap_sort(Container& A)
{
  std::size_t n = A.size();

  // sort as max-heap starting from last parent node
  for (int i = (n/2) - 1; i >= 0; --i) heap(A, i, n-1);

  for (int i = n-1; i > 0; --i)
  {
    std::swap(A[i], A[0]);
    heap(A, 0, i);
  }
}

template <typename Container>
void print(Container& C) {
  for (auto &e : C)
    std::cout << e << ' ';
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  std::vector<int> data =
    {9, 23, 24, 20, 18, 14, 17, 13, 15, 11, 10, 5, 7, 3, 2};

  print(data);

  heap_sort(data);

  print(data);

  return 0;
}
