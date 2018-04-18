////////////////////////////////////////////////////////////////////////////////
//
// Linked list cycle
// from https://leetcode.com/problems/linked-list-cycle/description/
//
// Description
// Given a linked list, determine if it has a cycle in it.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

bool has_cycle(ListNode* head)
{
  ListNode *slow_ptr{head}, *fast_ptr{head};
  while (fast_ptr && fast_ptr->next) {
    slow_ptr = slow_ptr->next;
    fast_ptr = fast_ptr->next->next;
    if (slow_ptr == fast_ptr) return true;
  }
  return false;
}

int main(int argc, char** argv)
{
  {
    ListNode* head{nullptr};
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);
    ListNode* node5 = new ListNode(5);

    {
      // cycle in one node
      node1->next = node1;

      std::cout << "cycle in one node: "
        << (has_cycle(node1) ? "yes" : "no") << std::endl;
    }

    {
      // cycle in two nodes
      node1->next = node2;
      node2->next = node1;

      std::cout << "cycle in two nodes: "
        << (has_cycle(node1) ? "yes" : "no") << std::endl;
    }

    {
      // cycle in many nodes
      node1->next = node2;
      node2->next = node3;
      node3->next = node4;
      node4->next = node5;
      node5->next = node1; // generate cycle

      std::cout << "cycle in many nodes: "
        << (has_cycle(node1) ? "yes" : "no") << std::endl;
    }

    {
      // no cycle
      node1->next = node2;
      node2->next = node3;
      node3->next = node4;
      node4->next = node5;
      node5->next = nullptr;

      std::cout << "many nodes with no cycle: "
        << (has_cycle(node1) ? "yes" : "no") << std::endl;
    }

    {
      // only one node with no cycle
      node1->next = nullptr;

      std::cout << "only one node with no cycle: "
        << (has_cycle(node1) ? "yes" : "no") << std::endl;
    }

    {
      // empty list
      std::cout << "empty list: "
        << (has_cycle(nullptr) ? "yes" : "no") << std::endl;
    }
  }

  return 0;
}
