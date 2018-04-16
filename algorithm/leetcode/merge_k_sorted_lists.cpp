///////////////////////////////////////////////////////////////////////////////
//
// Merge k Sorted Lists
// https://leetcode.com/problems/merge-k-sorted-lists/description/
//
// Description
// Merge k sorted lists and return it as one sorted list. Analyze and describe
// its complexity.
//
// Example
// Input:
// [
//    1->4->5,
//    1->3->4,
//    2->6
// ]
// output: 1->1->2->3->4->4->5->6
//
// Solution
// divide k into k - 1 times merging two lists
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

ListNode* merge_two_lists(ListNode* l1, ListNode* l2)
{
  if (l1 == nullptr) return l2;
  if (l2 == nullptr) return l1;

  if (l1->val <= l2->val)
  {
    l1->next = merge_two_lists(l1->next, l2);
    return l1;
  }
  else
  {
    l2->next = merge_two_lists(l1, l2->next);
    return l2;
  }
}

ListNode* merge_k_lists(std::vector<ListNode*> lists)
{
  if (lists.empty()) return nullptr;

  while (lists.size() > 1) {
    lists.push_back(merge_two_lists(lists[0], lists[1]));
    lists.erase(lists.begin());
    lists.erase(lists.begin());
  }
  return lists.front();
}

///////////////////////////////////////////////////////////////////////////////
// Helper function
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

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  std::vector<ListNode*> lists;

  ListNode* list1{nullptr};
  ListNode* list2{nullptr};
  ListNode* list3{nullptr};

  insert(&list1, 1);
  insert(&list1, 4);
  insert(&list1, 5);

  insert(&list2, 1);
  insert(&list2, 3);
  insert(&list2, 5);

  insert(&list3, 2);
  insert(&list3, 6);

  traverse(list1);
  traverse(list2);
  traverse(list3);

  lists.push_back(list1);
  lists.push_back(list2);
  lists.push_back(list3);

  ListNode* new_list = merge_k_lists(lists);
  traverse(new_list);

  return 0;
}
