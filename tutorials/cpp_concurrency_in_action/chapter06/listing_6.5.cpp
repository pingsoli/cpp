///////////////////////////////////////////////////////////////////////////////
//
// A simple queue with a dummy node
//
// NOTE: it's not thread safe, what's the problem ?
//
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <iostream>
#include <thread>
#include <iostream>
#include <mutex>

template <typename T>
class queue
{
private:
  struct node
  {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };

  std::unique_ptr<node> head;
  node* tail;

public:
  queue() :
    head{new node}, tail{head.get()}
  {}

  queue(const queue&) = delete;
  queue& operator=(const queue&) = delete;

  std::shared_ptr<T> try_pop()
  {
    if (head.get() == tail)
    {
      return std::make_shared<T>();
    }

    std::shared_ptr<T> const res(head->data);
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return res;
  }

  void push(T new_value)
  {
    std::shared_ptr<T> new_data(
        std::make_shared<T>(std::move(new_value)));
    std::unique_ptr<node> p(new node);
    tail->data = new_data;
    node* const new_tail = p.get();
    tail->next = std::move(p);
    tail = new_tail;
  }
};

queue<int> q;

// protect std::cout
std::mutex mut;

void produce(int start)
{
  for (unsigned i = 0; i < 10; ++i)
  {
    q.push(start + i);
    std::lock_guard<std::mutex> lk(mut);
    std::cout << ">>>>|  push " << start + i << std::endl;
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
      std::lock_guard<std::mutex> lk(mut);
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

  std::cout << std::endl;

  return 0;
}
