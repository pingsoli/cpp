///////////////////////////////////////////////////////////////////////////////
//
// Compute elapsed time
//
///////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <iostream>
#include <vector>

template <typename TimeT = std::chrono::milliseconds>
struct measure
{
  template <typename F, typename ...Args>
  static typename TimeT::rep execution(F&& func, Args&&... args)
  {
    auto start = std::chrono::steady_clock::now();
    std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
    auto duration = std::chrono::duration_cast<TimeT>
                             (std::chrono::steady_clock::now() - start);
    return duration.count();
  }
};

///////////////////////////////////////////////////////////////////////////////

void test(unsigned long loop_count)
{
  for (unsigned long i = 0; i < loop_count; ++i)
  {}
}

template <typename Iterator, typename T>
void foo(Iterator first, Iterator last, T init_value)
{
  for (auto it = first; it != last; ++it)
    std::cout << *it << ' ';

  test(9999);
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // simple solution

  std::chrono::steady_clock::time_point begin =
    std::chrono::steady_clock::now();

  test(100000);

  std::chrono::steady_clock::time_point end =
    std::chrono::steady_clock::now();

  std::cout << "time elapsed: "
    << std::chrono::duration_cast<
                    std::chrono::milliseconds>
                    (end - begin).count() << std::endl;

  /////////////////////////////////////////////////////////////////////////////
  //
  // Testing general function

  std::cout << "time elapsed: " << measure<>::execution(test, 100000)
    << std::endl;

  /////////////////////////////////////////////////////////////////////////////
  //
  // Testing template function

  typedef std::vector<int>::iterator iterator_type;
  std::vector<int> vi;

  std::cout << "time elapsed: "
    << measure<>::execution(foo<iterator_type, int>, vi.begin(), vi.end(), 100)
    << std::endl;

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
