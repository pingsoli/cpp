///////////////////////////////////////////////////////////////////////////////
//
// std::promise and std::future
// what's the relationship between them ?
//
///////////////////////////////////////////////////////////////////////////////

#include <future>
#include <iostream>
#include <thread>

void do_multiply(std::promise<int>&& int_promise, int a, int b) {
  int_promise.set_value(a * b);
}

struct Div {
  void operator()(std::promise<int>&& int_promise, int a, int b) const {
    int_promise.set_value(a / b);
  }
};

int main(int argc, char** argv)
{
  int a = 20;
  int b = 10;

  std::promise<int> mul_promise;
  std::promise<int> div_promise;

  // get the futures
  std::future<int> mul_future = mul_promise.get_future();
  std::future<int> div_future = div_promise.get_future();

  // calculate the result in a separate thread
  std::thread mul_thread(do_multiply, std::move(mul_promise), a, b);
  Div div;
  std::thread div_thread(div, std::move(div_promise), a, b);

  // get the results
  std::cout << "20 * 10 = " << mul_future.get() << std::endl;
  std::cout << "20 / 10 = " << div_future.get() << std::endl;

  mul_thread.join();
  div_thread.join();

  return 0;
}
