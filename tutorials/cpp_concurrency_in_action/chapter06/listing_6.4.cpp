///////////////////////////////////////////////////////////////////////////////
//
// A simple single-threaded queue inplementation
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <iostream>

template <typename T>
class queue
{
private:
  struct node
  {
    T data;
    std::unique_ptr<node> next;

    node(T data_) :
      data{std::move(data_)}
    {}
  };

  std::unique_ptr<node> head;
  node* tail;

public:
  queue() :
    tail{nullptr}
  {}

  queue(const queue&) = delete;
  queue& operator=(const queue&) = delete;

  std::shared_ptr<T> try_pop()
  {
    if (!head)
    {
      return std::shared_ptr<T>();
    }

    std::shared_ptr<T> const res(
        std::make_shared<T>(std::move(head->data)));
    const std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return res;
  }

  void push(T new_value)
  {
    std::unique_ptr<node> p(new node(std::move(new_value)));
    node* const new_tail = p.get();
    if (tail)
    {
      tail->next = std::move(p);
    }
    else
    {
      head = std::move(p);
    }
    tail = new_tail;
  }
};

int main(int argc, char** argv)
{
  queue<int> q;
  for (unsigned i = 0; i < 10; ++i)
  {
    q.push(i);
  }

  std::shared_ptr<int> pop_value;
  for (unsigned i = 0; i < 15; ++i)
  {
    pop_value = q.try_pop();
    if (pop_value)
      std::cout << "|<<<<  pop  " << *pop_value << std::endl;
  }

  return 0;
}
