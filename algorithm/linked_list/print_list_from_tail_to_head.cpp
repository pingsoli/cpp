////////////////////////////////////////////////////////////////////////////////
// print list from tail to head
// NO bidirectional list, just linked list.
//
// solution:
// using stack.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <iterator>

struct ListNode {
  int val;
  struct ListNode* next;
  ListNode(int value) : val(value), next(nullptr) {}
};

int main(int argc, char *argv[])
{
  ListNode node1(1);
  ListNode node2(2);
  ListNode node3(3);
  ListNode node4(4);
  ListNode node5(5);

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node5;

  ListNode* ptr = &node1;
  std::vector<ListNode*> vl;

  while (ptr) {
    vl.push_back(ptr);
    ptr = ptr->next;
  }

  for (auto it = vl.rbegin(); it != vl.rend(); ++it) {
    std::cout << (*it)->val << " -> ";
  }
  std::cout << "nullptr" << '\n';

  return 0;
}
