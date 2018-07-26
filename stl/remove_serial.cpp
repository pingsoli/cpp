#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

struct BadPredicate {
  bool operator() (const int i) {
    return ++times_called == 3;
  }

private:
  size_t times_called = 0;
};


int main(int argc, char *argv[])
{
  std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // why remove 3, 6 ? make clear of the remove_if algorithm,
  // remove_if algorithm get the BadPredicate copy, and in the inner loop,
  // create a another BadPredicate copy, and the `times_called` is cleared to 0.
  //
  // the possible implementation of std::remove_if
  // template<typename ForwardIter, typename Predicate>
  // ForwardIter remove_if(ForwardIter begin, ForwardIter end, Predicate p)
  // {
  //   begin = find_if(begin, end, p);
  //   if (begin == end) return begin;
  //   else {
  //     ForwardIter next = begin;
  //     return remove_copy_if(++next, end, begin, p); // create another copy
  //   }
  // }
  vi.erase(std::remove_if(begin(vi), end(vi), BadPredicate()), vi.end());
  std::copy(begin(vi), end(vi), std::ostream_iterator<int>(std::cout, " "));

  return 0;
}
