////////////////////////////////////////////////////////////////////////////////
// the following code simulates STL advance().
// This show how to use tag dispatching for controlling which function overload
// to pick based on the compile-time properties of the argument type.
//
// advantages of empty class as a tag to implement tag dispatch.
// the alternative way to use std::enable_if.
//
// References
// [1] https://stackoverflow.com/questions/4035179/advantages-of-an-empty-class-in-c
// [2] https://www.boost.org/community/generic_programming.html#tag_dispatching
// [3] https://akrzemi1.wordpress.com/examples/overloading-tag-dispatch/
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// these are all tags.
struct input_iterator_tag         {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};


// these are all kinds of iterators, connect with different tag.
struct InputIterator {
  using tag = input_iterator_tag;
  // ...
};

struct BidirectionalIterator {
  using tag = bidirectional_iterator_tag;
  // ...
};

struct RandomAccessIterator {
  using tag = random_access_iterator_tag;
  // ...
};


// these aer dispatches with different implementations.
template <typename InputIter, typename Distance>
void advance_dispatch(InputIter& i, Distance n, input_iterator_tag) {
  std::cout << "input iterator tag" << '\n';
  // ...
}

template <typename BidirectionalIter, typename Distance>
void advance_dispatch(BidirectionalIter& i, Distance n,
    bidirectional_iterator_tag) {
  std::cout << "bidirectional iterator tag" << '\n';
  // ...
}

template <typename RandomAccessIter, typename Distance>
void advance_dispatch(RandomAccessIter& i, Distance n,
    random_access_iterator_tag) {
  std::cout << "random access iterator tag" << '\n';
  // ...
}

// the final interface, we don't need to specify the iterator type by ourself,
// the compiler will do the job for us.
template <typename Iterator, typename Distance>
void advance(Iterator& i, Distance n) {
  advance_dispatch(i, n, typename Iterator::tag{});
}

int main(int argc, char *argv[])
{
  InputIterator         i_iter;
  BidirectionalIterator b_iter;
  RandomAccessIterator  r_iter;

  advance(i_iter, 5);
  advance(b_iter, 2);
  advance(r_iter, 1);

  return 0;
}
