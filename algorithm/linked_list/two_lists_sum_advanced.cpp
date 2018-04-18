////////////////////////////////////////////////////////////////////////////////
//
// Two Lists Sum Advanced
// Description
// Given two numbers represented by two linked lists, write a function that
// returns sum list.
// The sum list is linked list representation of additition of two input numbers
//
// Example
// Input:
//  First  list: 5->6->3  // represents number 563
//  Second list: 8->4->2  // represents number 842
// Output:
//  Resultant list: 1->4->0->5 // represents number 1405
//
// Challenge
// Not allowed to mofify the lists.
// Not allowed to use explicit extra space.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

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

ListNode* reverse(ListNode* head)
{
  ListNode* temp{nullptr}, *next_node{nullptr};

  while (head) {
    next_node = head->next;
    head->next = temp;
    temp = head;
    head = next_node;
  }
  return temp;
}

ListNode* add_sum(ListNode* l1, ListNode* l2)
{
  // reverse l1 and l2
  l1 = reverse(l1);
  l2 = reverse(l2);
  return reverse(add_two_numbers(l1, l2));
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

    insert_tail(&l1, 5);
    insert_tail(&l1, 6);
    insert_tail(&l1, 3);

    traverse(l1);

    insert_tail(&l2, 8);
    insert_tail(&l2, 4);
    insert_tail(&l2, 2);

    traverse(l2);

    l3 = add_sum(l1, l2);

    traverse(l3);
  }

  return 0;
}
