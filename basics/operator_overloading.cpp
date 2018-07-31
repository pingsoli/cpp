////////////////////////////////////////////////////////////////////////////////
// overload operator() function, make a class looks like a function
//
// Why overload operator() ?
// create a functor.
// details: https://stackoverflow.com/questions/317450/why-override-operator
//
// Use-case ?
// 1) std::for_each(), STL algorithms
// 2) sometimes, logger needs to overload operator().
//
// logger.log("hello world");  =>  logger("hello world");
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct Accumulator {
  int counter{0};
  int operator()(int i) { return counter += i; }
};

int main(int argc, char **argv)
{
  Accumulator acc;

//  std::cout << acc(10) << std::endl;  // print "10"
//  std::cout << acc(20) << std::endl;  // print "30"

  std::vector<int> vec{1, 2, 3};
  std::for_each(vec.begin(), vec.end(), std::ref(acc));
  // NOTE: remove the std::ref(), acc.counter will not increment
  // std::for_each(vec.begin(), vec.end(), acc);

  // acc contains the sum of all elements of the vector
  std::cout << acc.counter << std::endl;

  return 0;
}
