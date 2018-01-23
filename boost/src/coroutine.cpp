#include <iostream>
#include <functional>
#include <string>
#include <tuple>
#include <exception>
#include <boost/coroutine2/all.hpp>

using namespace boost::coroutines2;

// ####################################################################
// non-value
void coco_without_value(coroutine<void>::push_type& sink)
{
  std::cout << "Hello";
  sink();
  std::cout << "world";
}

void coco_without_value_test()
{
  coroutine<void>::pull_type source{ coco_without_value };

  std::cout << ", ";
  source();
  std::cout << "!" << std::endl;
}

// output: Hello, world!

// ####################################################################
// single-value
void coco_single_value(coroutine<int>::push_type& sink, int i)
{
  int j = i;
  sink(++j);
  sink(++j);
  std::cout << "end\n";
}

void coco_single_value_test()
{
  using namespace std::placeholders;
  coroutine<int>::pull_type source{
              std::bind(coco_single_value, _1, 0)};
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
void coco_multi_value(coroutine<std::tuple<int, std::string>>::pull_type& source)
{
  auto args = source.get();
  std::cout << std::get<0>(args) << " " << std::get<1>(args) << '\n';
  source();
  args = source.get();
  std::cout << std::get<0>(args) << " " << std::get<1>(args) << '\n';
}

void coco_multi_value_test()
{
  coroutine<std::tuple<int, std::string>>::push_type sink{ coco_multi_value };
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
void coco_with_exception(coroutine<void>::push_type& sink)
{
  sink();
  throw std::runtime_error("runtime error");
}

void coco_with_exception_test()
{
  coroutine<void>::pull_type source{ coco_with_exception };
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

// ####################################################################

int main(int argc, char** argv)
{
//  coco_without_value_test();
//  coco_single_value_test();
//  coco_multi_value_test();

  coco_with_exception_test();

  return 0;
}
