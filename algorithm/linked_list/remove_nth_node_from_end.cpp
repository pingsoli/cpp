////////////////////////////////////////////////////////////////////////////////
//
// Remove Nth node from end of list
// from http://www.lintcode.com/en/problem/remove-nth-node-from-end-of-list/
//
// Description
// Given a linked list, remove the n-th node from the end of list and return its
// head.
//
// Example
// Given 1->2->3->4->5->null, and n = 2.
// After removing the second node from the end, the linked list becomes
// 1->2->3->5->null.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

// how to find nth node ?
// 1) reverse the list, (bad)
// 2) slow-fast pointer, (good)
// the distance between slow pinter and fast pointer is n, the fast pointer
// will arrive the end of list, and slow will be nth node place.
ListNode* remove_nth_from_end(ListNode* head, int n)
{
  if (head == nullptr || n < 1) return head;

  ListNode dummy(0);
  dummy.next = head;
  ListNode* pre_del_node{&dummy};

  for (int i = 0; i != n; ++i) {
    if (!head) return dummy.next;
    head = head->next;
  }

  while (head) {
    head = head->next;
    pre_del_node = pre_del_node->next;
  }

  pre_del_node->next = pre_del_node->next->next;
  return dummy.next;
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
    ListNode* list{nullptr};
    int n = 2;

    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 3);
    insert_tail(&list, 4);
    insert_tail(&list, 5);

    traverse(list);

    list = remove_nth_from_end(list, n);

    traverse(list);
  }

  return 0;
}
