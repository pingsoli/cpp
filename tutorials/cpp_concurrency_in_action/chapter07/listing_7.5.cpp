///////////////////////////////////////////////////////////////////////////////
//
// The reference-counted reclamation machinery
//
///////////////////////////////////////////////////////////////////////////////

template <typename T>
class lock_free_stack
{
private:
  std::atomic<node*> to_be_deleted;

  static void delete_nodes(node* nodes)
  {
    while (nodes)
    {
      node* next = nodes->next;
      delete nodes;
      nodes = next;
    }
  }

  void try_reclaim(node* old_node)
  {
    if (threads_in_pop == 1) // trying to reclaim the node
    {
      node* nodes_to_delete = to_be_deleted.exchange(nullptr);
      if (!--threads_in_pop) // Are you the only thread in pop ?
      {
        delete_nodes(nodes_to_delete);
      }
      else
      {
        chain_pending_nodes(nodes_to_delete);
      }
      delete old_head;
    }
    else
    {
      chain_pending_node(old_head);
      --threads_in_pop;
    }
  }

  void chain_pending_nodes(node* nodes)
  {
    node* last = nodes;
    while (node* const next = last->next)
    {
      last = next;
    }
    chain_pending_nodes(nodes, last);
  }

  void chain_pending_nodes(node* first, node* last)
  {
    last->next = to_be_deleted;
    while (!to_be_deleted.compare_exchange_weak(
          last->next, first));
  }

  void chain_pending_node(node* n)
  {
    chain_pending_nodes(n, n);
  }
};
