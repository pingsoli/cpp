///////////////////////////////////////////////////////////////////////////////
//
// A lock-free stack that leaks nodes
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

template <typename T>
class lock_free_stack
{
  struct node
  {
    std::shared_ptr<T> data;
    node* next;

    node(T const& data) :
      data{std::make_shared<T>(data)},
      next{nullptr}
    {}
  };
  std::atomic<node*> head;

public:
  lock_free_stack() {}

  void push(T new_value)
  {
    node* new_node = new node(new_value);
    new_node->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node));
  }

  std::shared_ptr<T> pop()
  {
    node* old_head = head.load();
    while (old_head &&
        !head.compare_exchange_weak(old_head, old_head->next));
    return old_head ? old_head->data : std::shared_ptr<T>();
  }

  void traverse()
  {
  }
};

///////////////////////////////////////////////////////////////////////////////

lock_free_stack<int> stack;

std::mutex cout_mutex;

void produce(int start)
{
  for (int i = start; i < start + 10; ++i)
  {
    stack.push(i);
    std::lock_guard<std::mutex> lk(cout_mutex);
    std::cout << ">|  push  " << i << std::endl;
  }
}

void consume()
{
  std::shared_ptr<int> pop_value;
  for (int i = 0; i < 10; ++i)
  {
    pop_value = stack.pop();
    if (pop_value)
    {
      std::lock_guard<std::mutex> lk(cout_mutex);
      std::cout << "|<  pop  " << *pop_value << std::endl;
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

  return 0;
}
