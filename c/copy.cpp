#include <iostream>
#include <iterator>

template <typename InputIterator, typename OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator result)
{
  while (first != last)
    *result++ = *first++;
  return result;
}

int main(int argc, char *argv[])
{
  int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int b[20] = { 0 }; // initialize all elements to zero
  const int a_sz = sizeof(a) / sizeof(int);
  const int b_sz = sizeof(b) / sizeof(int);

  // plain pointer
  copy(a, a + 10, b); // copy first 10 elements to b array

  for (int i = 0; i < b_sz; ++i)
    std::cout << b[i] << ' ';
  std::cout << '\n';

  return 0;
}
