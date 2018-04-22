////////////////////////////////////////////////////////////////////////////////
//
// Sort list
// from https://leetcode.com/problems/sort-list/description/
//
// Description
// Sort a linked list in O(n log n) time using constant space complexity.
//
// Keyword
// Merge sort
//
// Example
// Input : 4 -> 2 -> 1 -> 3
// output: 1 -> 2 -> 3 -> 4
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode *next;

  ListNode(int x) : val{x} ,next{nullptr} {}
};

// Divide the linked list into two lists,
// while the first list contains first n nodes return the second list's head.
ListNode *split(ListNode *head, int n)
{
  for (int i = 1; head && i < n; ++i) head = head->next;

  if (!head) return nullptr;
  ListNode *second = head->next;
  head->next = nullptr;
  return second;
}

// Merged the two linked list l1 and l2, then appened the merged sorted linked
// list to the node head return the tail of the merged sorted linked list.
ListNode *merge(ListNode *l1, ListNode *l2, ListNode *head)
{
  ListNode *cur = head;
  while (l1 && l2) {
    if (l1->val > l2->val) {
      cur->next = l2;
      cur = l2;
      l2 = l2->next;
    } else {
      cur->next = l1;
      cur = l1;
      l1 = l1->next;
    }
  }

  cur->next = (l1 ? l1 : l2);
  while (cur->next) cur = cur->next;
  return cur;
}

ListNode *sort(ListNode *head) {
  if (!head || !(head->next)) return nullptr;

  // get the linked list's length
  ListNode *cur = head;
  int length = 0;
  while (cur) {
    ++length;
    cur = cur->next;
  }

  ListNode dummy(0);
  dummy.next = head;
  ListNode *left{nullptr}, *right{nullptr}, *tail{nullptr};
  for (int step = 1; step < length; step <<= 1) {
    cur = dummy.next;
    tail = &dummy;
    while (cur) {
      left = cur;
      right = split(left, step);
      cur = split(right, step);
      tail = merge(left, right, tail);
    }
  }
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
    ListNode *list{nullptr};
    insert_tail(&list, 8);
    insert_tail(&list, 2);
    insert_tail(&list, 4);
    insert_tail(&list, 1);
    insert_tail(&list, 9);
    insert_tail(&list, 5);
    insert_tail(&list, 3);

    traverse(list);

    list = sort(list);

    traverse(list);
  }

  return 0;
}
