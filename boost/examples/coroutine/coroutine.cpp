/*
 * Boost Coroutine2 Learning
 *
 * The execution of routines forms a parent-child relationship,
 * and child termiantes before the parent.
 *
 * child                parent
 *  "a"   ---- 1 --->     "1"
 *        <--- 2 ----
 *  "b"   ---- 3 --->     "2"
 *        <--- 4 ----
 *  "c"   ---- 5 --->     "3"
 *
 * So, coroutine likes routine, but is different.
 *
 * Q: how to make coroutine work in c++ ?
 * A: each coroutine has its own stack and control-block, so a jump
 * in the parent and child is possible.
 *
 * Q: key point?
 * A: stackfulness and first-class continuation.
 *    stackfulness: provide suspending from within a nested stackframe.
 *    first-class continuation: passed as an argument, returned by a
 *    function and stored in a data structure to be used later.
 */

#include <iostream>
#include <functional>
#include <string>
#include <tuple>
#include <exception>
#include <vector>
#include <iomanip>
#include <boost/coroutine2/all.hpp>

// It's bad habit, avoid to exposing namespace
using namespace boost::coroutines2;

// ####################################################################
// non-value
void coro_without_value(coroutine<void>::push_type& sink)
{
  std::cout << "Hello";
  sink();
  std::cout << "world";
}

void coro_without_value_test()
{
  coroutine<void>::pull_type source{ coro_without_value };

  std::cout << ", ";
  source();
  std::cout << "!\n";
}

// output: Hello, world!

// ####################################################################
// Lambda-expression looks more concise
void coro_with_lambda_expression()
{
  typedef boost::coroutines2::coroutine<void> coro_t;

//  coro_t::pull_type source{
//    [](coro_t::push_type& sink) {
//      std::cout << "Hello";
//      sink();
//      std::cout << "world";
//    }};
//
//  std::cout << ", ";
//  source();
//  std::cout << "!\n";

  // same approach, change the place of pull_type and push_type
  coro_t::push_type sink{
    [](coro_t::pull_type& source) {
      std::cout << ", ";
      source();
      std::cout << "!\n";
    }
  };

  std::cout << "Hello";
  sink();
  std::cout << "world";
  sink();
}

// ####################################################################
// single-value
void coro_single_value(coroutine<int>::push_type& sink, int i)
{
  int j = i;
  sink(++j);
  sink(++j);
  std::cout << "end\n";
}

void coro_single_value_test()
{
  using namespace std::placeholders;
  coroutine<int>::pull_type source{
              std::bind(coro_single_value, _1, 0)};
  std::cout << source.get() << '\n';
  source();
  std::cout << source.get() << '\n';
  source();
}

// output:
// 1
// 2
// end

// ####################################################################
// multi return value
void coro_multi_value(coroutine<std::tuple<int, std::string>>::pull_type& source)
{
  int item;
  std::string data;
  std::tie(item, data) = source.get();
  std::cout << item << " " << data << '\n';

// Use std::tie to unpack the tuple
//  auto args = source.get();
//  std::cout << std::get<0>(args) << " " << std::get<1>(args) << '\n';

  source();
  auto args = source.get();
  std::cout << std::get<0>(args) << " " << std::get<1>(args) << '\n';
}

void coro_multi_value_test()
{
  coroutine<std::tuple<int, std::string>>::push_type sink{ coro_multi_value };
  sink(std::make_tuple(0, "data"));
  sink(std::make_tuple(1, "bbb"));
  std::cout << "end\n";
}

// output:
// 0 data
// 1 bbb
// end

// ####################################################################
// exception-handling
void coro_with_exception(coroutine<void>::push_type& sink)
{
  sink();
  throw std::runtime_error("runtime error");
}

void coro_with_exception_test()
{
  coroutine<void>::pull_type source{ coro_with_exception };
  try
  {
    source();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

// output: runtime error

// #####################################################################
// Stack unwinding
// the coroutine is not-a-coroutine
// the coroutine is not complete
// the coroutine is not running
// the coroutine owns a stack

void coro_stack_unwind()
{
  struct X {
    X() { std::cout << "X()" << std::endl; }
    ~X() { std::cout << "~X()" << std::endl; }
  };

  typedef boost::coroutines2::coroutine<void> coro_t;

  coro_t::push_type sink(
    [&](coro_t::pull_type& source) {
      X x;
      for (int i = 0; ; ++i) {
        std::cout << "fn() " << i << std::endl;
        // transfer execution control back to main()
        source();
      }
    });

  sink();
  sink();
  sink();
  sink();
  sink();

  std::cout << "sink is complete: " << std::boolalpha << !sink << '\n';
}

// output:
// X()
// fn() 0
// fn() 1
// fn() 2
// fn() 3
// fn() 4
// sink is complete: false
// ~X()

// #####################################################################

int main(int argc, char** argv)
{
//  coro_without_value_test();
//  coro_single_value_test();
//  coro_multi_value_test();
//  coro_with_exception_test();
//  coro_stack_unwind();

  coro_with_lambda_expression();

  return 0;
}
