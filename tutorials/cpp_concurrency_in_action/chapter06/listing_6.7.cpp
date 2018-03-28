///////////////////////////////////////////////////////////////////////////////
//
// A thread-safe queue with locking and waiting: iternals and interface
//
///////////////////////////////////////////////////////////////////////////////

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
  std::mutex tail_mutex;
  std::unique_ptr<node> head;
  node* tail;
  std::condition_variable data_cond;

public:
  threadsafe_queue() :
    head{new node}, tail{head.get}
  {}

  threadsafe_queue(const threadsafe_queue&) = delete;
  threadsafe_queue& operator=(const threadsafe_queue&) = delete;

  std::shared_ptr<T> try_pop();
  bool try_pop(T& value);
  std::shared_ptr<T> wait_and_pop();
  void wait_and_pop(T& value);
  void push(T new_value);
  bool empty();
};
