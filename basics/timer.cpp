#include <chrono>
#include <iostream>
#include <thread>

class Timer
{
private:
  using clock_t = std::chrono::high_resolution_clock;
  using milli_t = std::chrono::duration<double, std::milli>;

  std::chrono::time_point<clock_t> m_begin;

public:
  Timer() : m_begin(clock_t::now())
  {
  }

  void reset()
  {
    m_begin = clock_t::now();
  }

  double elapsed() const {
    return std::chrono::duration_cast<milli_t>(clock_t::now() - m_begin).count();
  }
};

int main(int argc, char *argv[])
{
  Timer t;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << t.elapsed() << '\n';

  t.reset();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << t.elapsed() << '\n';

  return 0;
}
