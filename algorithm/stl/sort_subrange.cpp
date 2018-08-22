////////////////////////////////////////////////////////////////////////////////
// sort the selected range from given container.
//
// think about it ? how ?
// just get sort the part we want. maybe you think of partial_sort().
// partial_sort() is the part of the answer, but not all.
//
// hints:
// you don't have to sort the whole container.
//
// Solution:
// use the nth_element() to make nth is in place.
// use partition_sort to the get the sorted sub range.
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

template <typename I>// RandomAccessIterator only
void sort_subrange(I f, I l, I sf, I sl)
{
  if (sf == sl) return;
  if (sf != f) {
    std::nth_element(f, sf, l);
    ++sf;
  }

  std::partial_sort(sf, sl, l);
}

template <typename I>
void print(I f, I l) {
  for (; f != l; ++f)
    std::cout << *f << " ";
  std::cout << '\n';
}

int main(int argc, char *argv[])
{
  std::vector<int> vi { 10, 2, 8, 19, 1, 5, 7, 9, 2, 4, 9, 10, 3, 6 };

  for (auto& f : vi)
    std::cout << f << ' ';
  std::cout << '\n';

  // the sub range we want to sort.
  auto sf = begin(vi) + 4;
  auto sl = begin(vi) + 8;

  // sort the subrange
  sort_subrange(begin(vi), end(vi), sf, sl);

  print(begin(vi), end(vi));
  std::cout << "sub range: ";
  print(sf, sl);

  return 0;
}
