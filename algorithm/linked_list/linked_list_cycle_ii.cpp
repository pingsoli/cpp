////////////////////////////////////////////////////////////////////////////////
//
// Linked list cycle II
// from https://leetcode.com/problems/linked-list-cycle-ii/description/
//
// Description
// Given a linked list, return the node where the cycle begins. if there is no
// cycle, return null.
//
// NOTE: Do not modify the linked list.
//
// Analysis
//
// |<---------- list length --------->|
// |             |<-- cycle length -->|
// |
//              C1     C2     Ci      Cr
// 1 ---> 2 ---> 3 ---> 6 ---> I ---> 8
//               ^                    |
// |         |   |--------------------+
// |<- n-r ->|
//
// list's nodes number: n
// cycle nodes number:  r
//
// first meet at Ci node
// slow: (n-r+i)
// fast: 2*(n-r+i)
//
// second meet
// reset fast to start place, next time will meet in entry.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

ListNode* detect_cycle(ListNode* head)
{
  if (!head || !(head->next)) return nullptr;

  ListNode* slow{head}, *fast{head};

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) {            // there is a cycle
      fast = head;
      while (slow != fast) {
        fast = fast->next;
        slow = slow->next;
      }
      return slow;
    }
  }
  return nullptr;
}

int main(int argc, char** argv)
{
  {
    ListNode node1(1);
    ListNode node2(2);
    ListNode node3(3);
    ListNode node4(6);
    ListNode node5(0);
    ListNode node6(8);
    ListNode* found_entry{nullptr};

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node3;

    found_entry = detect_cycle(&node1);

    if (found_entry)
      std::cout << "Found the entry: " << found_entry->val << std::endl;
    else
      std::cout << "No cycle" << std::endl;
  }

  return 0;
}
