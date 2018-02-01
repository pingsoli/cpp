/*
 * future  -> asynchronous
 * promise -> generate asynchronous results
 */
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <string>

#include <boost/fiber/all.hpp>

inline
int fn(std::string const& str, int n)
{
  for (int i = 0; i < n; ++i)
  {
    std::cout << i << ": " << str << std::endl;
    boost::this_fiber::yield();
  }
  return n;
}

void start()
{
  boost::fibers::future<int> fi(
    boost::fibers::async(
      std::bind(fn, "abc", 5)));
  fi.wait();
  std::cout << "fn() returned " << fi.get() << std::endl;
}

int main(int argc, char** argv)
{

  try {
    boost::fibers::fiber(start).join();
    std::cout << "done." << std::endl;
  } catch (std::exception const& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }

  return 0;
}
