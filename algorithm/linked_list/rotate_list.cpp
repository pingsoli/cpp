////////////////////////////////////////////////////////////////////////////////
//
// Rotate list
// from https://leetcode.com/problems/rotate-list/description/
//
// Description
// Given a linked list, rotate the list to the right by k places, where k is
// non-negative.
//
// Example
// Input: 1->2->3->4->5->NULL, k = 2
// Output: 4->5->1->2->3->NULL
//
// Explanation:
// rotate 1 steps to the right: 5->1->2->3->4->NULL
// rotate 2 steps to the right: 4->5->1->2->3->NULL
//
// Input: 0->1->2->NULL, k = 4
// Output: 2->0->1->NULL
//
// Explanation:
// rotate 1 steps to the right: 2->0->1->NULL
// rotate 2 steps to the right: 1->2->0->NULL
// rotate 3 steps to the right: 0->1->2->NULL
// rotate 4 steps to the right: 2->0->1->NULL
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int      val;
  ListNode *next;

  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *rotate_right(ListNode *head, int k) {
  if (!head) return head;

  int len = 1; // number of nodes
  ListNode *new_header, *tail;
  new_header = tail = head;

  while (tail->next) {  // get the numbe of nodes in the list
    tail = tail->next;
    len++;
  }
  tail->next = head;    // circle the link

  if (k %= len) {
    for (int i = 0; i < len-k; ++i) tail = tail->next; // the tail node is the
                                // (len - k)-th node (1st node is head)
  }

  new_header = tail->next;
  tail->next = nullptr;
  return new_header;
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
    ListNode *list = nullptr;
    int k = 3;

    std::cout << list << std::endl;
    insert_tail(list, 0);
    insert_tail(list, 1);
    insert_tail(list, 2);

    traverse(list);

//    list = rotate_right(list, k);
//
//    traverse(list);
  }

  return 0;
}
