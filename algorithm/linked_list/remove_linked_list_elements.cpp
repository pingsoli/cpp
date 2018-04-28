////////////////////////////////////////////////////////////////////////////////
//
// Remove linked list elements
// from https://leetcode.com/problems/remove-linked-list-elements/description/
//
// Description
// Remove all elements from a linked list of integers that have value val.
//
// Example
// Given : 1 -> 2 -> 6 -> 3 -> 4 -> 5 -> 6, val = 6;
// return: 1 -> 2 -> 3 -> 4 -> 5.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode *next{nullptr};

  ListNode(int x) : val{x}, next{nullptr} {}
};

// ListNode *remove_elements(ListNode *head, int val) {
//   ListNode **pp = &head;
//   while (*pp && (*pp)->val == val) *pp = (*pp)->next;
//
//   ListNode *prev{nullptr}, *curr{head};
//   while (curr) {
//     if (curr->val == val) prev->next = curr->next;
//     prev = curr;
//     curr = curr->next;
//   }
//   return head;
// }

ListNode *remove_elements(ListNode *head, int val) {
  ListNode **list = &head;
  ListNode *temp{nullptr};

  while (*list) {
    if ((*list)->val == val)
    {
      temp = *list;
      *list = (*list)->next;
      delete temp;
    }
    else
    {
      list = &(*list)->next;
    }
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
    std::cout << head->val << "(" << &head << ") -> ";
    head = head->next;
  }
  std::cout << "null" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  {
    ListNode *list{nullptr};

    insert_tail(&list, 6);
    insert_tail(&list, 6);
    insert_tail(&list, 6);
    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 6);
    insert_tail(&list, 3);
    insert_tail(&list, 4);
    insert_tail(&list, 5);
    insert_tail(&list, 6);

    traverse(list);

    list = remove_elements(list, 6);

    traverse(list);
  }

  return 0;
}
