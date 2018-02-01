#include <cassert>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

struct stringize_functor {
private:
  std::string& result;

public:
  explicit stringize_functor(std::string& res)
    : result(res)
  {}

  template <class T>
  void operator()(const T& v) const {
    result += boost::lexical_cast<std::string>(v);
  }
};

/*
 * boost::fusion works for boost::tuple
 */
template <class Sequence>
std::string stringize(const Sequence& seq) {
  std::string result;
  boost::fusion::for_each(seq, stringize_functor(result));
  return result;
}

int main(int argc, char** argv)
{
  boost::tuple<char, int, char, int> decim('-', 10, 'e', 5);
//  assert(stringize(decim) == "-10e5");
  std::cout << stringize(decim) << std::endl;

  std::pair<int, std::string> value_and_type(270, "pingsoli");
//  assert(stringize(value_and_type) == "270pingsoli");
  std::cout << stringize(value_and_type) << std::endl;

  return 0;
}
