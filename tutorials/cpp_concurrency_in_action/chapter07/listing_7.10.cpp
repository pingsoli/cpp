///////////////////////////////////////////////////////////////////////////////
//
// Pushing a node on a lock-free stack using split reference counts
//
///////////////////////////////////////////////////////////////////////////////

template <typename T>
class lock_free_stack
{
private:
  struct node;

  // external/internal count technique
  // The sum of these values is the total nubmer of references to the node.
  // The external count is kept alongside the pointer to the node and is
  // increased every time the pointer is read. When the reader is finished
  // with the node, it decreases the internal count.
  // Once the internal count is equal to zero, there are no outstanding
  // references to the node and it can be safely deleted.
  struct counted_node_ptr
  {
    int external_count;
    node* ptr;
  };

  struct node
  {
    std::shared_ptr<T> data;
    std::atomic<int>   internal_count;
    counted_node_ptr   next;

    node(T const& data):
      data{std::make_shared(data)},
      internal_count{0}
    {}
  };

  std::atomic<counted_node_ptr> head;

public:
  ~lock_free_stack()
  {
    while (pop());
  }

  void push(T const& data)
  {
    counted_node_ptr new_node;
    new_node.ptr = new node(data);
    new_node.external_count = 1;
    new_node.ptr->next = head.load();
    while (!head.compare_exchange_weak(new_node.ptr->next, new_node));
  }
};
