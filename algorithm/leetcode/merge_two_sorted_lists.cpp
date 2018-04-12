///////////////////////////////////////////////////////////////////////////////
//
// Merge Two Sorted Lists
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct ListNode {
  int      val;
  ListNode *next;
  ListNode(int value) : val{value}, next{nullptr} {}
};

///////////////////////////////////////////////////////////////////////////////
//
// recursive solution

ListNode* merge_two_lists(ListNode* l1, ListNode* l2)
{
  if (l1 == nullptr) return l2;
  if (l2 == nullptr) return l1;

  if (l1->val < l2->val) {
    l1->next = merge_two_lists(l1->next, l2);
    return l1;
  } else {
    l2->next = merge_two_lists(l1, l2->next);
    return l2;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// non-recursive solution

ListNode* merge_two_sorted_lists_1(ListNode* l1, ListNode* l2)
{
  ListNode dummy(0);
  ListNode* tail = &dummy;

  while (l1 && l2)
  {
    if (l1->val <= l2->val)
    {
      tail->next = l1;
      l1 = l1->next;
    } else {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }

  tail->next = l1 ? l1 : l2;
  return dummy.next;
}

///////////////////////////////////////////////////////////////////////////////
//
// helper function

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

struct printer
{
  std::string msg;

  printer(const std::string& message) :
    msg{message}
  {
    std::cout << '\n' << msg;
  }

  ~printer()
  {
    std::cout << std::endl;
  }
};

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // test recursive solution

  {
    printer("recursive version");
    ListNode* list1{nullptr};
    insert(&list1, 1);
    insert(&list1, 5);
    insert(&list1, 3);

    ListNode* list2{nullptr};
    insert(&list2, 2);
    insert(&list2, 0);
    insert(&list2, 4);

    traverse(list1);
    traverse(list2);

    ListNode* new_list{nullptr};
    new_list = merge_two_lists(list1, list2);

    traverse(new_list);
  }

  {
    printer("list1 and list2 are both empty");
    ListNode* list1{nullptr}, *list2{nullptr};
    ListNode* new_list{nullptr};

    new_list = merge_two_lists(list1, list2);

    traverse(new_list);
  }

  {
    printer("one of list1 and list1 is empty");
    ListNode* list1{nullptr}, *list2{nullptr};
    ListNode* new_list{nullptr};

    insert(&list1, 1);
    insert(&list1, 0);
    insert(&list1, 3);

    traverse(list1);
    traverse(list2);

    new_list = merge_two_lists(list1, list2);

    traverse(new_list);
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // test non-recursive solution

  {
    printer("non-recursive version");
    ListNode* list1{nullptr};
    insert(&list1, 1);
    insert(&list1, 5);
    insert(&list1, 3);

    ListNode* list2{nullptr};
    insert(&list2, 2);
    insert(&list2, 0);
    insert(&list2, 4);

    traverse(list1);
    traverse(list2);

    ListNode* new_list{nullptr};

    new_list = merge_two_sorted_lists_1(list1, list2);

    traverse(new_list);
  }

  {
    printer("list1 and list2 are both empty");
    ListNode* list1{nullptr}, *list2{nullptr};
    ListNode* new_list{nullptr};

    new_list = merge_two_sorted_lists_1(list1, list2);

    traverse(new_list);
  }

  {
    printer("one of list1 and list1 is empty");
    ListNode* list1{nullptr}, *list2{nullptr};
    ListNode* new_list{nullptr};

    insert(&list1, 1);
    insert(&list1, 0);
    insert(&list1, 3);

    traverse(list1);
    traverse(list2);

    new_list = merge_two_sorted_lists_1(list1, list2);

    traverse(new_list);
  }


  return 0;
}
