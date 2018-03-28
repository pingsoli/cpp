///////////////////////////////////////////////////////////////////////////////
//
// A thread-safe queue with fine-grained locking
//
// make clear of the pop and push operations
//
// push operation just involve the tail pointer
// pop operation just change the head smart pointer
//
// use two mutexs to protect the data: tail and head pointer
//
///////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <thread>
#include <memory>
#include <iostream>

template <typename T>
class threadsafe_queue
{
private:
  struct node
  {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };

  std::mutex head_mutex;
  std::unique_ptr<node> head;
  std::mutex tail_mutex;
  node* tail;

  node* get_tail()
  {
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    return tail;
  }

  /////////////////////////////////////////////////////////////////////////////

  // It's thread-safe
  std::unique_ptr<node> pop_head()
  {
    std::lock_guard<std::mutex> head_lock(head_mutex);

    if (head.get() == get_tail())
      return nullptr;

    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return old_head;
  }

  // It's not thread-safe, can you see any problem?
  // std::unique_ptr<node> pop_head()
  // {
  //   node* const old_tail = get_tail(); // get old tail value outside lock on
                                          // head_mutex
  //   std::lock_guard<std::mutex> head_lock(head_mutex);
  //   if (head.get() == old_tail)
  //     return nullptr;

  //   std::unique_ptr<node> old_head = std::move(head);
  //   head = std::move(old_head->next);
  //   return old_head;
  // }

  /////////////////////////////////////////////////////////////////////////////

public:
  threadsafe_queue() :
    head{new node}, tail{head.get()}
  {}

  threadsafe_queue(const threadsafe_queue&) = delete;
  threadsafe_queue& operator=(const threadsafe_queue&) = delete;

  std::shared_ptr<T> try_pop()
  {
    std::unique_ptr<node> old_head = pop_head();
    return old_head ? old_head->data : std::shared_ptr<T>();
  }

  void push(T new_value)
  {
    std::shared_ptr<T> new_data(
        std::make_shared<T>(new_value));
    std::unique_ptr<node> p(new node);
    node* const new_tail = p.get();
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    tail->data = new_data;
    tail->next = std::move(p);
    tail = new_tail;
  }
};

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
    pop_value = q.try_pop();
    if (pop_value)
    {
      std::lock_guard<std::mutex> cout_lock(cout_mutex);
      std::cout << "|<<<<  pop  " << *pop_value << std::endl;
    }
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
