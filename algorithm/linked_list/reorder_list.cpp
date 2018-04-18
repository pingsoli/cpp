////////////////////////////////////////////////////////////////////////////////
//
// Reorder list
// from https://leetcode.com/problems/reorder-list/description/
//
// Description
// Given a singly linked list L: l0 -> l1 -> .... -> Ln-1 -> Ln
// reorder it to: L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...
//
// You must do this in-place without altering the node's values
//
// Example
// Given 1->2->3->4.
// reorder it to: 1->4->2->3.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

// slow-fast pointer and reverse the left part between slow and fast pointer
void reorder(ListNode* head)
{
  if (!head || !(head->next)) return ;

  ListNode *slow{head}, *fast{head};

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *r_head = slow->next;
  slow->next = nullptr;

  // reverse list on the right side
  ListNode *temp{nullptr};
  ListNode *prev{nullptr};
  while (r_head) {
    temp = r_head->next;
    r_head->next = prev;
    prev = r_head;
    r_head = temp;
  }

  // merge two list
  r_head = prev;
  ListNode* l_head = head;
  ListNode* temp1{nullptr};
  ListNode* temp2{nullptr};

  while (l_head && r_head) {
    temp1 = l_head->next;
    l_head->next = r_head;
    temp2 = r_head->next;
    r_head->next = temp1;

    l_head = temp1;
    r_head = temp2;
  }
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
    std::cout << "\nthe example\n";
    ListNode* list{nullptr};

    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 3);
    insert_tail(&list, 4);

    traverse(list);

    reorder(list);

    traverse(list);
  }

  {
    std::cout << "\nodd nodes\n";
    ListNode *list{nullptr};

    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 3);
    insert_tail(&list, 4);
    insert_tail(&list, 5);

    traverse(list);

    reorder(list);

    traverse(list);
  }

  return 0;
}
