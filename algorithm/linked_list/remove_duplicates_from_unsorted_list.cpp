////////////////////////////////////////////////////////////////////////////////
//
// remove duplicates from unsorted list
// from http://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-linked-list/
//
// Description
// write a remove_duplicates function which takes a list and deletes any
// dumplicate nodes from the list. the list is not sorted.
//
// Example
// Given 12->11->12->21->41->43->21, return 12->11->21->41->43
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

// Time Complexity
// O (1/2 n ^ 2)
ListNode* delete_duplicates(ListNode* head)
{
  if (head == nullptr) return nullptr;

  ListNode* curr{head};
  ListNode* inner{nullptr};
  ListNode* temp{nullptr};

  while (curr) {
    inner = curr;
    while (inner->next) {
      if (inner->next->val == curr->val) {
        temp = inner->next;
        inner->next = inner->next->next;
        delete temp;
      } else {
        inner = inner->next;
      }
    }
    curr = curr->next;
  }
  return head;
}

////////////////////////////////////////////////////////////////////////////////
//Helper function

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

    insert_tail(&list, 12);
    insert_tail(&list, 11);
    insert_tail(&list, 12);
    insert_tail(&list, 21);
    insert_tail(&list, 41);
    insert_tail(&list, 43);
    insert_tail(&list, 21);

    traverse(list);

    list = delete_duplicates(list);

    traverse(list);
  }

  {
    std::cout << "\nmultiple continuous duplicate nodes\n";
    ListNode* list{nullptr};

    insert_tail(&list, 12);
    insert_tail(&list, 12);
    insert_tail(&list, 12);

    traverse(list);

    list = delete_duplicates(list);

    traverse(list);
  }

  {
    std::cout << "\nmultiple continuous duplicate nodes in the tail of list\n";
    ListNode* list{nullptr};

    insert_tail(&list, 43);
    insert_tail(&list, 12);
    insert_tail(&list, 12);
    insert_tail(&list, 12);

    traverse(list);

    list = delete_duplicates(list);

    traverse(list);

  }

  return 0;
}
