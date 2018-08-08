
// advantage
// 1) type less code. specify deleter for smart pointer like std::shared_ptr.
// 2) as a predicate for STL algorithms.
//
// C++14 has a more powerful lambda expression, can replace std::bind at most place.
// template deduction.
//
// precaute the references dangle and pointer dangle in lambda.

#include <iterator>
#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>

template <typename... Args>
decltype(auto) size(Args&&... args) {
  return sizeof...(args);
}

int main(int argc, char *argv[])
{
  {
    std::vector<int> vi = {10, 5, 2, 20, 1, 8};

    // work with STL algorithm
    auto it = std::find_if(std::begin(vi), std::end(vi),
        [] (int val) { return 1 < val && val < 10; });

    std::cout << *it << '\n';
  }

  {
    // how to copy the only moveable object, such as std::unique_ptr
    std::unique_ptr<int> upi = std::make_unique<int>(10);

    // move a moveable object to a closure. in c++14.
    auto func = [upi = std::move(upi)] (int val) {
                  std::cout << *upi << '\n';
                };
    func(1);
  }

  {
    // make lambda variadic
    auto f = [] (auto&&... params)
             {
               return size(params...);
             };

    std::cout << f("hello", " world", "!") << '\n';
  }

  return 0;
}
