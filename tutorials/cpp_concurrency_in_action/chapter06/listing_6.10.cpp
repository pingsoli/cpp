///////////////////////////////////////////////////////////////////////////////
//
// A thread-safe queue with locking and waiting: try_pop() and empty()
// full implementation
//
///////////////////////////////////////////////////////////////////////////////

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

template <typename T>
class threadsafe_queue
{
private:
  struct node
  {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };

  std::mutex              head_mutex;
  std::mutex              tail_mutex;
  std::unique_ptr<node>   head;
  node*                   tail;
  std::condition_variable data_cond;

  node* get_tail()
  {
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    return tail;
  }

  std::unique_ptr<node> pop_head()
  {
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return old_head;
  }

  std::unique_lock<std::mutex> wait_for_data() // 2
  {
    std::unique_lock<std::mutex> head_lock(head_mutex);
    data_cond.wait(head_lock, [&] { return head.get() != get_tail(); });
    return std::move(head_lock);  // 3
  }

  std::unique_ptr<node> wait_pop_head() // 4
  {
    std::unique_lock<std::mutex> head_lock(wait_for_data());
    return pop_head();
  }

  std::unique_ptr<node> wait_pop_head(T& value)
  {
    std::unique_lock<std::mutex> head_lock(wait_for_data());  // 5
    value = std::move(*head->data);
    return pop_head();
  }

  std::unique_ptr<node> try_pop_head()
  {
    std::lock_guard<std::mutex> head_lock(head_mutex);
    if (head.get() == get_tail())
      return std::unique_ptr<node>();
    return pop_head();
  }

  std::unique_ptr<node> try_pop_head(T& value)
  {
    std::lock_guard<std::mutex> head_lock(head_mutex);
    if (head.get() == get_tail())
      return std::unique_ptr<node>();

    value = std::move(*head->data);
    return pop_head();
  }

public:
  threadsafe_queue() :
    head{new node}, tail{head.get()}
  {}

  threadsafe_queue(const threadsafe_queue&) = delete;
  threadsafe_queue& operator=(const threadsafe_queue&) = delete;

  std::shared_ptr<T> try_pop()
  {
    std::unique_ptr<node> old_head = try_pop_head();
    return old_head ? old_head->data : std::shared_ptr<T>();
  }

  bool try_pop(T& value)
  {
    std::unique_ptr<node> const old_head = try_pop_head(value);
    return old_head ? true : false;
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_ptr<node> const old_head = wait_pop_head();
    return old_head->data;
  }

  void wait_and_pop(T& value)
  {
    std::unique_ptr<node> const old_head = wait_pop_head(value);
  }

  void push(T new_value)
  {
    std::shared_ptr<T> new_data(
        std::make_shared<T>(new_value));
    std::unique_ptr<node> p(new node);
    {
      node* const new_tail = p.get();
      std::lock_guard<std::mutex> tail_lock(tail_mutex);
      tail->data = new_data;
      tail->next = std::move(p);
      tail = new_tail;
    }
    data_cond.notify_one();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> head_lock(head_mutex);
    return (head.get() == get_tail());
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// test threadsafe_queue wait_and_pop

threadsafe_queue<int> q;

// protect cout
std::mutex cout_mutex;

void produce(int start)
{
  for (unsigned i = 0; i < 10; ++i)
  {
    q.push(i + start);
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << ">>>>|  push " << i + start << std::endl;
  }
}

void consume()
{
  std::shared_ptr<int> pop_value;
  for (unsigned i = 0; i < 10; ++i)
  {
    pop_value = q.wait_and_pop();
    if (pop_value)
    {
      std::lock_guard<std::mutex> cout_lock(cout_mutex);
      std::cout << "|<<<<  pop  " << *pop_value << std::endl;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

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

  std::cout << std::endl;

  return 0;
}
