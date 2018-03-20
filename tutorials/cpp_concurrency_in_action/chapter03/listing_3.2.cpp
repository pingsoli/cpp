///////////////////////////////////////////////////////////////////////////////
//
// Accidentally passing out a reference to protected data
//
///////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <iostream>

class some_data
{
  int a;
  std::string b;
public:
  void do_something()
  {
    std::cout << "we gain the reference and manipulate the data" << std::endl;
  }
};

class data_wrapper
{
private:
  some_data data;
  std::mutex m;
public:
  template <typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    func(data);
  }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
  unprotected = &protected_data;
}

data_wrapper x;

void foo()
{
  x.process_data(malicious_function);
  unprotected->do_something();
}

int main(int argc, char** argv)
{
  foo();
  return 0;
}
