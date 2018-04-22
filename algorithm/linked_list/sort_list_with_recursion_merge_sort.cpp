////////////////////////////////////////////////////////////////////////////////
//
// Sort list
// from https://leetcode.com/problems/sort-list/discuss/
//
// Merge sort recursion version
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int val;
  ListNode *next;

  ListNode(int x) : val{x}, next{nullptr} {}
};

ListNode *find_middle(ListNode *head)
{
  if (!head || !(head->next)) return head;

  ListNode *slow = head, *fast = head->next;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}

ListNode *merge(ListNode *l1, ListNode *l2)
{
  ListNode dummy(0);
  ListNode *last_node{&dummy};

  while (l1 && l2) {
    if (l1->val < l2->val) {
      last_node->next = l1;
      l1 = l1->next;
    } else {
      last_node->next = l2;
      l2 = l2->next;
    }
    last_node = last_node->next;
  }

  last_node->next = (l1 ? l1 : l2);
  return dummy.next;
}

ListNode *sort(ListNode *head)
{
 if (!head || !(head->next)) return head;

 ListNode *mid_node = find_middle(head);
 ListNode *r_list = sort(mid_node->next);
 mid_node->next = nullptr;
 ListNode *l_list = sort(head);

 return merge(l_list, r_list);
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
    ListNode *list{nullptr};
    insert_tail(&list, 8);
    insert_tail(&list, 2);
    insert_tail(&list, 4);
    insert_tail(&list, 1);
    insert_tail(&list, 9);
    insert_tail(&list, 5);
    insert_tail(&list, 3);

    traverse(list);

    list = sort(list);

    traverse(list);
  }

  return 0;
}
