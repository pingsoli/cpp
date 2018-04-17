////////////////////////////////////////////////////////////////////////////////
//
// Remove duplicates from sorted list II
// from https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
//
// Description
// Given a sorted linked list, delete all nodes that have duplicate numbers,
// leaving distinct numbers from the original list.
//
// Example
// Given 1->2->3->3->4->4->5, return 1->2->5.
// Given 1->1->1->2->3, return 2->3.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

// how to remember the current node ?
// dummy node, and integer to remember the deleting value
ListNode* delete_duplicates(ListNode* head)
{
  if (head == nullptr) return nullptr;

  ListNode dummy(0);
  dummy.next = head;

  ListNode* node = &dummy;

  while (node->next && node->next->next) {
    if (node->next->val == node->next->next->val) {
      int val_prev = node->next->val;

      while (node->next && val_prev == node->next->val) {
        ListNode* tmp = node->next;
        node->next = node->next->next;
        delete tmp;
      }
    } else {
      node = node->next;
    }
  }
  return dummy.next;
}

////////////////////////////////////////////////////////////////////////////////
// insert into list by order
void insert(ListNode** head, int value)
{
  ListNode* new_node = new ListNode(value);
  ListNode* curr_node{*head}, *prev_node{*head};

  // empty list
  if (*head == nullptr) {
    *head = new_node;
    return;
  }

  // insert before the head node
  if (new_node->val < (*head)->val) {
    new_node->next = *head;
    *head = new_node;
    return;
  }

  while (curr_node) {
    if (new_node->val < curr_node->val) {
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
    ListNode* list{nullptr};

    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    insert(&list, 3);
    insert(&list, 4);
    insert(&list, 4);
    insert(&list, 5);

    traverse(list);

    list = delete_duplicates(list);

    traverse(list);
  }

  return 0;
}
