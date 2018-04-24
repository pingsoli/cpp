////////////////////////////////////////////////////////////////////////////////
//
// Swap nodes in pairs
// from https://leetcode.com/problems/swap-nodes-in-pairs/description/
//
// Description
// Given a linked list, swap everty two adjacent nodes and return its head.
//
// Example
// Given 1->2->3->4, you should return the list as 2->1->4->3.
//
// NOTE
// Your algorithm should use only constant extra space.
// You may not modify the vaules in the list's node, only nodes itself may be
// changed.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode *next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

// my implementation
ListNode *swap_pairs(ListNode *head) {
  if (!head || !(head->next)) return head;

  ListNode dummy(0);
  ListNode *prev{&dummy}, *curr{head}, *next{nullptr};

  while (curr && (next = curr->next)) {
    curr->next = next->next;
    next->next = curr;
    prev->next = next;

    prev = curr;
    curr = curr->next;
  }
  return dummy.next;
}

// Simplest version from leetcode
ListNode *swap_pairs_1(ListNode *head)
{
  ListNode **pp = &head, *a, *b;
  while ((a = *pp) && (b = a->next)) {
    a->next = b->next;
    b->next = a;
    *pp = b;
    pp = &(a->next);
  }
  return head;
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
    ListNode *list{nullptr};
    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 3);
    insert_tail(&list, 4);

    traverse(list);

//    list = swap_pairs(list);
    list = swap_pairs_1(list);

    traverse(list);
  }

  return 0;
}
