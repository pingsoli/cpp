////////////////////////////////////////////////////////////////////////////////
//
// two star pointer
//
// remove elements from linked list, we can make use of two star pointer.
// there will need only one temporary variable.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode *next;

  ListNode(int x) : val(x), next(nullptr) {}
};

void change_head(ListNode *head) {
  ListNode **node = &head;
  ListNode *new_node = new ListNode(0);

  std::cout << "head address: " << head << std::endl;

//  node = &new_node;  // change the node's value
//  *node = new_node;  // change the head value

  std::cout << "head address: " << head << std::endl;
}

ListNode *remove_element(ListNode *head, int val)
{
  ListNode **node = &head;
  ListNode *temp = nullptr;

  while (*node) {
    if ((*node)->val == val) {
      temp = *node;
      *node = (*node)->next;
      delete temp;
    } else {
      node = &(*node)->next;
    }
  }
  return head;
}

void insert_tail(ListNode **head, int val)
{
  ListNode *new_node = new ListNode(val);
  if (!(*head)) {
    *head = new_node;
    return;
  }

  ListNode *node = *head;
  while (node->next)
    node = node->next;

  node->next = new_node;
}

void traverse(ListNode *head)
{
  while (head) {
    std::cout << head->val << " -> ";
    head = head->next;
  }
  std::cout << "null" << std::endl;
}

int main(int argc, char** argv)
{
  {
    ListNode *list = nullptr;

    change_head(list);
  }

  {
    ListNode *list = nullptr;

    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 3);

    traverse(list);

    list = remove_element(list, 2);

    traverse(list);
  }

  return 0;
}
