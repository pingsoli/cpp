////////////////////////////////////////////////////////////////////////////////
// cohabitate std::shared_ptr and boost::shared_ptr
//
// when use boost::log library, we cannot pass a std::shared_ptr as a parameter.
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <boost/shared_ptr.hpp>
#include <iostream>

template <typename T>
boost::shared_ptr<T> make_shared_ptr(std::shared_ptr<T>& ptr) {
  return boost::shared_ptr<T>(ptr.get(), [ptr] (T*) mutable { ptr.reset(); });
}

template <typename T>
std::shared_ptr<T> make_shared_ptr(boost::shared_ptr<T>& ptr) {
  return std::shared_ptr<T>(ptr.get(), [ptr] (T*) mutable { ptr.reset(); });
}

int main(int argc, char *argv[])
{
  std::shared_ptr<int> spi = std::make_shared<int>(5);
  boost::shared_ptr<int> bpi = make_shared_ptr<int>(spi);
  spi = make_shared_ptr<int>(bpi);

  std::cout << *bpi << '\n';
  std::cout << *spi << '\n';

  std::cout << spi.use_count() << '\n';
  std::cout << bpi.use_count() << '\n';

  return 0;
}
