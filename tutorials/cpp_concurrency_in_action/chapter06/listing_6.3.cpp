///////////////////////////////////////////////////////////////////////////////
//
// A thread-safe queue holding std::thread_ptr<> instances
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <iostream>

template <typename T>
class threadsafe_queue
{
private:
  std::mutex mut;
  std::queue<std::shared_ptr<T>> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue() {}

  threadsafe_queue(const threadsafe_queue& other) = delete;
  threadsafe_queue& operator=(const threadsafe_queue&) = delete;

  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = std::move(*data_queue.front());
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    std::shared_ptr<T> res = data_queue.front();
    return res;
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;

    value = std::move(*data_queue.front());
    data_queue.pop();
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;

    std::shared_ptr<T> res = data_queue.front();
    return res;
  }

  void push(T new_value)
  {
    std::shared_ptr<T> data(
        std::make_shared<T>(std::move(new_value)));
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};

threadsafe_queue<int> q;

// protect std::cout
std::mutex mu;

void produce(int start)
{
  for (unsigned i = start; i < start + 10; ++i)
  {
    q.push(i);
    std::lock_guard<std::mutex> lk(mu);
    std::cout << "|<<<<  push " << i << std::endl;
  }
}

void consume()
{
  int value;
  for (unsigned i = 0; i < 10; ++i)
  {
    q.wait_and_pop(value);
    std::lock_guard<std::mutex> lk(mu);
    std::cout << ">>>>|  pop  " << value << std::endl;
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
