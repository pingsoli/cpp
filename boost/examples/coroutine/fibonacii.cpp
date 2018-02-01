#include <boost/coroutine2/all.hpp>
#include <iostream>

int main()
{
  typedef boost::coroutines2::coroutine<int> coro_t;

  coro_t::pull_type source(
    [&](coro_t::push_type& sink) {
      int first = 1, second = 1;
      sink(first);
      sink(second);
      for (int i = 0; i < 8; ++i) {
        int third = first + second;
        first = second;
        second = third;
        sink(third);
      }
    });

  // How come we can do this?
  // coroutine<>::pull_type provides input iterators and
  // std::begin()/std::end() are overload. the increment-operation switches
  // the context and transfer data.
  for (auto i : source)
    std::cout << i << " ";
  std::cout << '\n';

  // Think about the design of pull and push?
  // I want to get the data, so I pull it.
  // I want to transfer to outside, so I push it.
  //
  // Another question?
  // rewrite the following code, change the pull and push place?

  coro_t::push_type sink(
    [&](coro_t::pull_type &source) {
      // pull the data and print
      for (auto s : source)
        std::cout << s << " ";
    }
  );

  std::cout << "Please enter fibonacci number count you want: ";
  int count;
  if (!(std::cin >> count)) return 1;

  int first = 1, second = 1;
  sink(first);   // push the first
  sink(second);  // push the second
  for (int i = 0; i < count; ++i) {
    int third = first + second;
    first = second;
    second = third;
    sink(third);
  }

  std::cout << '\n';

  return 0;
}
