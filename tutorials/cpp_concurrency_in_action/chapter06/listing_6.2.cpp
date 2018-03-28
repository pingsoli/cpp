///////////////////////////////////////////////////////////////////////////////
//
// The full class definition for a thread-safe queue using condition variable
//
///////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <iostream>
#include <thread>

template <typename T>
class threadsafe_queue
{
private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue()
  {}

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(mut);
    data_queue.push(std::move(new_value));
    data_cond.notify_one();
  }

  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lock(mut);
    data_cond.wait(lock, [this]{ return !data_queue.empty(); });
    value = std::move(data_queue.front());
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lock(mut);
    data_cond.wait(lock, [this]{ return !data_queue.empty(); });
    std::shared_ptr<T> res(
        std::make_shared(std::move(data_queue.front())));
    data_queue.pop();
    return res;
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;
    value = std::move(data_queue.front());
    data_queue.pop();
  }

  bool empty() const
  {
    return data_queue.empty();
  }
};

threadsafe_queue<int> q;

// protect std::cout
std::mutex m;

void produce(int start)
{
  for (unsigned i = start; i < start + 10; ++i)
  {
    q.push(i);
  }
}

void consume()
{
  int value;
  for (unsigned i = 0; i < 10; ++i)
  {
    q.wait_and_pop(value);

    std::lock_guard<std::mutex> lk(m);
    std::cout << ">>>  pop " << value << std::endl;
  }
}

int main(int argc, char** argv)
{
  std::thread t1(produce, 0);
  std::thread t2(produce, 10);

  std::thread t3(consume);
  std::thread t4(consume);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  return 0;
}
