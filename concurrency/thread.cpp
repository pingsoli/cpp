////////////////////////////////////////////////////////////////////////////////
// thread
//
// 1. call regular function
//    1.1 without parameter
//    1.2 with parameter by value
//    1.3 with parameter by reference
//
// 2. call class member function
//    2.1 call member function inside.
//    2.2 call member function outside.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <thread>

void foo() {
  std::cout << "void foo()" << '\n';
}

void bar(int x) {
  std::cout << x << '\n';
}

void baz(int& x) {
  x = 1000;
}

class Test {
public:
  void no_state_member_function(const std::string& message) {
    std::cout << message << '\n';
  }

  void test() {
    std::cout << "test method" << '\n';
  }

  std::thread spawn() {
    return std::thread(
        [this] { this->test(); }
    );
  }

private:
  int data = 0;
};

int main(int argc, char *argv[])
{
  {
    int x = 0;
    std::thread thread1(foo); // no parameter
    std::thread thread2(bar, 2); // with parameter
    std::thread thread3(baz, std::ref(x)); // pass parameter with reference

    // wait to finish.
    thread1.join();
    thread2.join();
    thread3.join();

    // NOTE: put the following code before thread.join(), you may get wrong
    // output.
    std::cout << "x = " << x << '\n';
  }

  {
    Test test;
    std::thread thread1(&Test::no_state_member_function, test, "test"); // outside
    std::thread thread2(test.spawn()); // inside

    thread1.join();
    thread2.join();
  }

  {
    std::thread thread1(foo);
    std::thread thread2(bar, 20);
    // thread3 is now running() bar, thread2 is no longer a thread.
    std::thread thread3(std::move(thread2));

    thread1.join();
    thread3.join();
  }

  return 0;
}
