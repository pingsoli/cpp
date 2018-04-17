////////////////////////////////////////////////////////////////////////////////
//
// Add two numbers
// from https://leetcode.com/problems/add-two-numbers/description/
//
// Description
// You are given non-empty linked list representing two non-negative integers.
// The digits are stored in reverse order and each of their nodes contain a
// single digit. Add two numbers are return it as a linked list.
//
// You may assume the tow numbers do not contain any leading zero, except the
// number 0 itself.
//
// Example
// Input: ( 2 -> 4 -> 3 ) + ( 5 -> 6 -> 4 )
// Output: 7 -> 0 -> 8
//
// Explanation: 342 + 465 = 708
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode (int x) : val{x}, next{nullptr} {}
};

// carry bits
ListNode* add_two_numbers(ListNode* l1, ListNode* l2)
{
  ListNode dummy(0), *p{&dummy};
  int carry = 0;

  while (l1 || l2 || carry) {
    int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
    carry = sum / 10;
    p->next = new ListNode(sum % 10);
    p = p->next;
    l1 = l1 ? l1->next : l1;
    l2 = l2 ? l2->next : l2;
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
    ListNode* l1{nullptr};
    ListNode* l2{nullptr};
    ListNode* l3{nullptr};

    insert_tail(&l1, 2);
    insert_tail(&l1, 4);
    insert_tail(&l1, 3);

    insert_tail(&l2, 5);
    insert_tail(&l2, 6);
    insert_tail(&l2, 4);

    l3 = add_two_numbers(l1, l2);

    traverse(l3);
  }

  {
    ListNode* l1{nullptr};
    ListNode* l2{nullptr};
    ListNode* l3{nullptr};

    insert_tail(&l1, 6);
    insert_tail(&l1, 2);
    insert_tail(&l1, 5);

    insert_tail(&l2, 6);
    insert_tail(&l2, 6);
    insert_tail(&l2, 7);
    insert_tail(&l2, 1);

    l3 = add_two_numbers(l1, l2);

    traverse(l3);
  }

  return 0;
}
