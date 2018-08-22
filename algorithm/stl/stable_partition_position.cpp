////////////////////////////////////////////////////////////////////////////////
// let the selected items to top, other to bottom.
// It's a kind if sorting algorithm.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <vector>

template <typename I,
          typename P>
auto stable_partition_position(I f, I l, P p) -> I
{
  auto n = l - f;
  if (n == 0) return f;
  if (n == 1) return f + p(f);

  auto m = f + (n / 2);
  return std::rotate(stable_partition_position(f, m, p),
                     m,
                     stable_partition_position(m, l, p));
}

int main(int argc, char *argv[])
{
  using namespace std;

  int  a[] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
  bool b[] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 };

  auto p = stable_partition_position(begin(a), end(a), [&] (auto i) {
      return *(begin(b) + (i - begin(a)));
  });

  // output the result
  for (auto f = begin(a), l = p; f != l; ++f) cout << *f << " ";
  cout << "^ ";
  for (auto f = p, l = end(a); f != l; ++f) cout << *f << " ";
  cout << endl;

  return 0;
}
