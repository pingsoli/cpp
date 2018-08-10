// std::async basic function intro

// the flag about std::launch::async and std::launch::defered
// async: a new thread is launched to execute the task asynchronously.
// defered: the task is executed on the calling thread the first time its result
//          is requested(lazy evaluation)
// more detail: https://en.cppreference.com/w/cpp/thread/launch

#include <future>
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
  {
    // std::launch::async and std::launch::derfered differences
    //
    // std::async([] { .... }); what policy will the std::async use ?
    // the default policy is std::launch::async or std::launch::defered, choose
    // one of them randomly.
    using namespace std::literals;

    // running instantly on separated thread.
    auto async_fut = std::async(std::launch::async, [] {
        std::cout << "running instantly (depend on OS schduling)" << '\n';
        std::this_thread::sleep_for(2s);
        return 1;
      });

    // lazy evaluation, if we don't use lazy_fut.get(), the function will
    // not be called.
    auto lazy_fut = std::async(std::launch::deferred, [] {
        std::cout << "lazy evaluation" << '\n';
        std::this_thread::sleep_for(2s);
        return 2;
      });

    std::this_thread::sleep_for(2s);
    std::cout << "main thread running" << '\n';

    // what will happen here ?
    auto result1 = async_fut.get();
    // auto result2 = lazy_fut.get();
  }

  return 0;
}
