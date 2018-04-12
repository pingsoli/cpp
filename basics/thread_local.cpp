///////////////////////////////////////////////////////////////////////////////
//
// thread_local since c++11
// if a variable is thread_local then each thread has its own copy.
//
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <iostream>

thread_local int i = 0;

void f(int new_val) {
  i = new_val;
}

void g() {
  std::cout << i << '\n';
}

void thread_func(int id) {
  f(id);
  ++i;
  g();
}

///////////////////////////////////////////////////////////////////////////////
//
// Passing thread_local by address to another thread

void another_thread(int* p)
{
  *p = 42;
}

///////////////////////////////////////////////////////////////////////////////

struct X {
  X() {
    std::cout << "hello";
  }

  ~X() {
    std::cout << "goodbye";
  }
};

void foo() {
  thread_local X x;
}

void do_nothing() {}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

  // general usage
  {
    i = 9;

    std::thread t1(thread_func, 1);
    std::thread t2(thread_func, 2);
    std::thread t3(thread_func, 3);

    t1.join();
    t2.join();
    t3.join();

    std::cout << i << std::endl; // main thread
  }

  /////////////////////////////////////////////////////////////////////////////

  // passing address by pointer to another thread
  // another thread modify thread_local variable
  {
    i = 9;
    std::thread t1(another_thread, &i);
    t1.join();
    std::cout << i << std::endl; // 42
  }

  /////////////////////////////////////////////////////////////////////////////

  {
    std::thread t1(do_nothing);
    t1.join();
  }

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
