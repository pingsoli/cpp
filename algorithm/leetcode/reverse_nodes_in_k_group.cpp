///////////////////////////////////////////////////////////////////////////////
//
// Reverse Nodes in K-Group
//
// Given a linked list, reverse the nodes of a linked list k at a time and
// return its modified list
//
// k is a positive integer and is less than or equal to the lenght of the
// linked list. If the number of the nodes is not a multiple of k then left-out
// nodes in the end should remain as it is.
//
// Example
// Given this linked list: 1->2->3->4->5
// For k = 2, you should return: 2->1->4->3->5
// For k = 3, you should return: 3->2->1->4->5
//
// NOTE:
// 1) Only constant extra memory is allowed
// 2) You may not alter the values in the list's nodes, only nodes itself may
// be changed
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

struct ListNode {
  int val;
  ListNode* next;

  ListNode() : next{nullptr} {} // For creating dummy node
  ListNode(int x) : val{x}, next{nullptr} {}
};

// wrong solution of my own
// ListNode* reverse_k_group(ListNode* head, int k)
// {
//   ListNode dummy;
//   ListNode* curr_node{head};
//   ListNode* next_node{nullptr};
//   ListNode* new_head{nullptr};
//
//   ListNode* prev_group_tail{nullptr};
//   ListNode* curr_group_tail{nullptr};
//
//   int count{0};
//
//   while (curr_node) {
//     next_node = curr_node->next;
//
//     if (count == 0)
//       curr_group_tail = curr_node;
//
//     if (count == k)
//     {
//       // first group has no previous group, it's new head node
//       if (!prev_group_tail)
//         new_head = dummy.next;
//       else
//         prev_group_tail->next = dummy.next;
//
//       dummy.next = nullptr;
//       prev_group_tail = curr_group_tail;
//       count = 0; // clear the count
//     }
//     else
//     {
//       // Reverse nodes
//       curr_node->next = dummy.next;
//       dummy.next = curr_node;
//
//       curr_node = next_node;
//       ++count;
//     }
//   }
//
//   if (dummy.next)
//     prev_group_tail->next = dummy.next;
//
//   return new_head;
// }

ListNode* reverse_k_group(ListNode* head, int k)
{
  if (head == nullptr || k == 1) return head;

  int num = 0;
  std::shared_ptr<ListNode> preheader{new ListNode(-1)};
  preheader->next = head;
  ListNode* cur = preheader.get(), *nex, *pre = preheader.get();

  while (cur = cur->next) num++;

  while (num >= k) {
    cur = pre->next;
    nex = cur->next;

    for (int i = 1; i < k; ++i) {
      cur->next = nex->next;
      nex->next = pre->next;
      pre->next = nex;
      nex = cur->next;
    }

    pre = cur;
    num -= k;
  }
  return preheader->next;
}

void insert(ListNode** head, int value)
{
  ListNode* new_node = new ListNode(value);
  ListNode* curr_node = *head, *prev_node = *head;

  // empty list
  if (*head == nullptr)
  {
    *head = new_node;
    return;
  }

  // insert before the head node
  if (new_node->val < (*head)->val)
  {
    new_node->next = *head;
    *head = new_node;
    return;
  }

  curr_node = (*head)->next;

  while (curr_node) {

    if (new_node->val < curr_node->val)
    {
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

int main(int argc, char** argv)
{
  ListNode* head{nullptr};
  int k{0};

  {
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 5);

    traverse(head);

    std::cout << "please enter your k value: ";
    std::cin >> k;

    head = reverse_k_group(head, k);

    traverse(head);
  }

  return 0;
}
