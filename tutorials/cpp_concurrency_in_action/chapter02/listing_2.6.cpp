///////////////////////////////////////////////////////////////////////////////
//
// scoped_thread and example usage
//
///////////////////////////////////////////////////////////////////////////////

#include <thread>

class scoped_thread
{
  std::thread t;
public:
  explicit scoped_thread(std::thread t_)
    : t{std::move(t_)}
  {
    // why add this ? security checking ?
    if (!t.joinable())
      throw std::logic_error("No thread");
  }

  ~scoped_thread()
  {
    t.join();
  }

  scoped_thread(const scoped_thread&) = delete;
  scoped_thread& operator=(const scoped_thread&) = delete;
};

void do_something(int& i)
{
  ++i;
}

struct func
{
  int& i;

  func(int& i_) : i{i_} {}

  void operator()()
  {
    for (unsigned j = 0; j < 1000000; ++j)
      do_something(i);
  }
};

void do_something_in_current_thread()
{}

void f()
{
  int some_local_state;
  scoped_thread t(std::thread(func(some_local_state)));

  do_something_in_current_thread();
}

int main(int argc, char** argv)
{
  f();
  return 0;
}
