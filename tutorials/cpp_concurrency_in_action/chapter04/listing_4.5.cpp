///////////////////////////////////////////////////////////////////////////////
//
// Full class definition for a thread-safe queue using condition variables
//
// how to avoid deaklock ?
// using the same sequence of locking
//
///////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <memory>
#include <iostream>

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

  threadsafe_queue(const threadsafe_queue& other)
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue = other.data_queue;
  }

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{ return !data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return std::shared_ptr<T>();

    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    return res;
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};

threadsafe_queue<int> queue;
std::mutex io_mutex;

void produce(int start)
{
  for (int i = start; i < start + 10; ++i)
  {
    queue.push(i);

    std::unique_lock<std::mutex> lk(io_mutex);
    std::cout << "<<<< push [" << std::this_thread::get_id() << "] "
      << i << std::endl;
  }
}

void consume(int num)
{
  int value;

  for (int i = 0; i < num; ++i)
  {
    value = *queue.wait_and_pop();

    std::unique_lock<std::mutex> lk(io_mutex);
    std::cout << ">>>> pop [" << std::this_thread::get_id() << "] "
      << value << std::endl;
  }
}

int main(int argc, char** argv)
{
  for (int i = 0; i < 100; ++i)
  {
    std::thread t1(produce, 0);
    std::thread t2(produce, 10);

    std::thread t3(consume, 5);
    std::thread t4(consume, 15);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }

  return 0;
}
