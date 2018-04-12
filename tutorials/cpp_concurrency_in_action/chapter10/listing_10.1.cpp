///////////////////////////////////////////////////////////////////////////////
//
// An example test for concurrent push() and pop() calls on a queue
//
///////////////////////////////////////////////////////////////////////////////

#include <future>
#include <iostream>
#include <memory>

#include "threadsafe_queue.hpp"

void test_concurrent_push_and_pop_on_empty_queue()
{
  threadsafe_queue<int> q;

  std::promise<void> go, push_ready, pop_ready;
  std::shared_future<void> ready(go.get_future());

  std::future<void>                 push_done;
  std::future<std::shared_ptr<int>> pop_done;

  try
  {
    push_done = std::async(std::launch::async,
                  [&q, ready, &push_ready] ()
                  {
                    push_ready.set_value();
                    ready.wait();
                    q.push(42);
                  });

    pop_done = std::async(std::launch::async,
                  [&q, ready, &pop_ready] ()
                  {
                    pop_ready.set_value();
                    ready.wait();
                    return q.try_pop();
                  });

    push_ready.get_future().wait();
    pop_ready.get_future().wait();
    go.set_value();

    push_done.get();

    std::shared_ptr<int> ptr = pop_done.get();
    if (ptr)
      std::cout << *ptr << std::endl;

    std::cout << std::boolalpha << q.empty() << std::endl;
  }
  catch (...)
  {
    go.set_value();
    throw;
  }
}

int main(int argc, char** argv)
{
  test_concurrent_push_and_pop_on_empty_queue();
  return 0;
}
