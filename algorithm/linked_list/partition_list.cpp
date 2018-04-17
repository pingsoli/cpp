////////////////////////////////////////////////////////////////////////////////
//
// Partition list
// from https://leetcode.com/problems/partition-list/description/
//
// Description
// Given a linked list and a value x, partition it such that all nodes less than
// x come before nodes greater than or equal to x.
// you should preserve the original relative order of the nodes in each of the
// two partitions.
//
// Example
// Given  1->4->3->2->5->2 and x = 3.
// return 1->2->2->4->3->5.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode (int x) : val{x}, next{nullptr} {}
};

// given x, using two dummy nodes. They store the node that is bigger of smaller
// than x separately.
// return the next node of smaller list at last.
ListNode* partition(ListNode* head, int x)
{
  ListNode smaller_head(0), bigger_head(0);
  ListNode* smaller{&smaller_head}, *bigger{&bigger_head};

  while (head) {
    if (head->val < x)
      smaller = smaller->next = head;
    else
      bigger = bigger->next = head;
    head = head->next;
  }
  bigger->next = nullptr; // cannot omit
  smaller->next = bigger_head.next;
  return smaller_head.next;
}

////////////////////////////////////////////////////////////////////////////////
// Helper function
void insert_tail(ListNode** head, int val)
{
  ListNode* new_node = new ListNode(val);
  ListNode* node{*head};

  if (*head == nullptr) {
    *head = new_node;
    return;
  }

  while (node->next)
    node = node->next;

  node->next = new_node;
}

void traverse(ListNode* head)
{
  while (head) {
    std::cout << head->val << " -> ";
    head = head->next;
  }
  std::cout << "null" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  {
    std::cout << "\nthe example\n";
    ListNode* list{nullptr};

    insert_tail(&list, 1);
    insert_tail(&list, 4);
    insert_tail(&list, 3);
    insert_tail(&list, 2);
    insert_tail(&list, 5);
    insert_tail(&list, 2);

    traverse(list);

    list = partition(list, 3);

    traverse(list);
  }

  {
    std::cout << "\nempty list\n";
    ListNode* list{nullptr};

    traverse(list);

    list = partition(list, 2);

    traverse(list);
  }

  return 0;
}
