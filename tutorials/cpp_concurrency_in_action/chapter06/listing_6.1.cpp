///////////////////////////////////////////////////////////////////////////////
//
// A class definition for a thread-safe stack
//
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <mutex>
#include <iostream>
#include <stack>
#include <memory>
#include <exception>

struct empty_stack : std::exception
{
  const char* what() const throw()
  {
    return "empty stack";
  }
};

template <typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  threadsafe_stack() {}
  threadsafe_stack(const threadsafe_stack& other)
  {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  threadsafe_stack& operator=(const threadsafe_stack&) = delete;

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
  }

  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();
    std::shared_ptr<T> const res(
        std::make_shared<T>(std::move(data.top())));
    data.pop();
    return res;
  }

  void pop(T& value)
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();

    value = std::move(data.top());
    data.pop();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

threadsafe_stack<int> s;

void produce(int push_value)
{
  s.push(push_value);
}

void consume()
{
  int value;
  s.pop(value);
}

int main(int argc, char** argv)
{
  std::thread t1(produce, 10);
  std::thread t2(produce, 20);

  std::thread t3(consume);
  std::thread t4(consume);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  return 0;
}
