////////////////////////////////////////////////////////////////////////////////
//
// Remove duplicates from sorted list
// from https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
//
// Description
// Given a sorted linked list, delete all duplicates such that each element
// appear only once.
//
// Example
// Given 1->1->2, return 1->2
// Given 1->1->2->3->3, return 1->2->3
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

// NOTE: remember to release the memory
ListNode* delete_duplicates(ListNode* head)
{
  ListNode* curr_node{head};
  ListNode* tmp{nullptr};

  while (curr_node) {
    while (curr_node->next && curr_node->val == curr_node->next->val) {
      tmp = curr_node->next;
      curr_node->next = curr_node->next->next;
      delete(tmp);
      tmp = nullptr;
    }
    curr_node = curr_node->next;
  }
  return head;
}

////////////////////////////////////////////////////////////////////////////////
// Helper function
void insert(ListNode** head, int value)
{
  ListNode* new_node = new ListNode(value);
  ListNode* curr_node = *head, *prev_node = *head;

  // empty list
  if (*head == nullptr)
  {
    *head = new_node;
    return;
  }

  // insert before the head node
  if (new_node->val < (*head)->val)
  {
    new_node->next = *head;
    *head = new_node;
    return;
  }

  curr_node = (*head)->next;

  while (curr_node) {

    if (new_node->val < curr_node->val)
    {
      new_node->next = curr_node;
      prev_node->next = new_node;
      return;
    }

    prev_node = curr_node;
    curr_node = curr_node->next;
  }

  // insert new node into tail of the list
  prev_node->next = new_node;
}

void traverse(ListNode* head)
{
  while (head) {
    std::cout << head->val << " -> ";
    head = head->next;
  }
  std::cout << "null\n";
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  {
    std::cout << "general test\n";
    ListNode* list{nullptr};

    insert(&list, 1);
    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    insert(&list, 3);

    traverse(list);

    list = delete_duplicates(list);

    traverse(list);
  }

  {
    std::cout << "Empty list test\n";
    ListNode* list{nullptr};

    list = delete_duplicates(list);
    traverse(list);
  }

  return 0;
}

