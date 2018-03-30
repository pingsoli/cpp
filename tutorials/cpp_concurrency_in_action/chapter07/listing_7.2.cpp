///////////////////////////////////////////////////////////////////////////////
//
// Implementing push() without locks
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <iostream>

template <typename T>
class lock_free_stack
{
  struct node
  {
    T data;
    node* next;

    node(T const& data_) :
      data{data_}, next{nullptr}
    {}
  };
  std::atomic<node*> head;

public:
  lock_free_stack()
  {}

  void push(T new_value)
  {
    node* const new_node = new node(new_value);
    new_node->next = head.load();

    // set the head pointer to new node.
    // compare_exchange_weak ensure that the head pointer still has
    // the same value as you stored in new_node->next, and you set it to
    // new_node if so.
    while (!head.compare_exchange_weak(new_node->next, new_node));
  }
  void traverse()
  {
    node* n = head.load();
    while (n)
    {
      std::cout << n->data << " -> ";
      n = n->next;
    }
    std::cout << std::endl;
  }
};

///////////////////////////////////////////////////////////////////////////////

lock_free_stack<int> stack;

void produce(int start)
{
  for (unsigned i = 0; i < 10; ++i)
  {
    stack.push(i + start);
  }
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  std::thread t1(produce, 0);
  std::thread t2(produce, 10);

  t1.join();
  t2.join();

  stack.traverse();

  return 0;
}
