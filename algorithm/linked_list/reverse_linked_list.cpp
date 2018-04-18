////////////////////////////////////////////////////////////////////////////////
//
// Reverse linked list
// from https://leetcode.com/problems/reverse-linked-list/description/
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode (int x) : val{x}, next {nullptr} {}
};

//non-recursive version
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

// recursive version
ListNode* reverse_1(ListNode* head)
{
  if (!head || !(head->next)) return head;
  ListNode* node = reverse_1(head->next);

  head->next->next = head;
  head->next = nullptr;
  return node;
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
    std::cout << "\nnon-recursive version\n";
    ListNode* list{nullptr};

    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 3);
    insert_tail(&list, 4);

    traverse(list);

    list = reverse(list);

    traverse(list);
  }

  {
    std::cout << "\nrecursive version\n";
    ListNode* list{nullptr};

    insert_tail(&list, 1);
    insert_tail(&list, 2);
    insert_tail(&list, 3);
    insert_tail(&list, 4);

    traverse(list);

    list = reverse(list);

    traverse(list);
  }

  return 0;
}
