////////////////////////////////////////////////////////////////////////////////
//
// Copy list with random pointer
// from https://leetcode.com/problems/copy-list-with-random-pointer/description/
//
// Description
// A linked list is given such that each node contains an additional random
// pointer which could point to any node in the list or null.
//
// Return a deep copy of the list.
//
// Solution:
// 1) hash table
// 2) without hash table
// 3) hash table with recursion
//
//         +---------+
//         |         v
// Origin: 1 -> 2 -> 3 -> 4 -> 5 -> null
//
// New:    1'-> 2'-> 3'-> 4'-> 5'-> null
//
// Merge origin and new list
//         +------------------+
//         |                  v
// Merged: 1 -> 1'-> 2 ->2'-> 3 -> 3'-> 4 -> 4'-> 5 -> 5'->null
//
// Modify:
//         +------------------+
//         |                  v
//         1 -> 1'-> 2 ->2'-> 3 -> 3'-> 4 -> 4'-> 5 -> 5'->null
//              |                  ^
//              +------------------+
//
// Separate:
//         +---------+
//         |         v
//         1'-> 2'-> 3'-> 4'-> 5'-> null
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <unordered_map>

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label{x}, next{nullptr}, random{nullptr} {}
};

////////////////////////////////////////////////////////////////////////////////
// Solution 1: without hash table (3 times loop)
RandomListNode *copy_random_list(RandomListNode *head)
{
  RandomListNode *new_head, *l1{nullptr}, *l2{nullptr};

  // copy and merge to original list
  for (l1 = head; l1 != nullptr; l1 = l1->next->next) {
    l2 = new RandomListNode(l1->label);
    l2->next = l1->next;
    l1->next = l2;
  }

  new_head = head->next;
  for (l1 = head; l1 != nullptr; l1 = l1->next->next) {
    if (l1->random) l1->next->random = l1->random->next;
  }

  // extract the copied list
  for (l1 = head; l1 ; l1 = l1->next) {
    l2 = l1->next;
    l1->next = l2->next;
    if (l2->next) l2->next = l2->next->next;
  }

  return new_head;
}

////////////////////////////////////////////////////////////////////////////////
// Solution 2: hash table (1 time loop)
RandomListNode *copy_random_list_2(RandomListNode *head)
{
  RandomListNode dummy(0);
  RandomListNode *curr{&dummy};
  std::unordered_map<RandomListNode *, RandomListNode *> hash_map;

  while (head) {
    // link new node to new list
    RandomListNode *new_node{nullptr};

    if (hash_map.count(head) > 0) {
      new_node = hash_map[head];
    } else {
      new_node = new RandomListNode(head->label);
      hash_map[head] = new_node;
    }

    curr->next = new_node;
    // re-mapping old random node to new node
    if (head->random) {
      if (hash_map.count(head->random) > 0) {
        new_node->random = hash_map[head->random];
      } else {
        new_node->random = new RandomListNode(head->random->label);
        hash_map[head->random] = new_node->random;
      }
    }

    head = head->next;
    curr = curr->next;
  }

  return dummy.next;
}
////////////////////////////////////////////////////////////////////////////////
// Solution 3: hash table with recursion
std::unordered_map<RandomListNode *, RandomListNode *> hmap;

RandomListNode *copy_random_list_3(RandomListNode *head)
{
  if (!head) return nullptr;
  if (hmap.find(head) != hmap.end())
    return hmap.find(head)->second;

  RandomListNode* node = new RandomListNode(head->label);
  hmap[head] = node;
  node->next = copy_random_list_3(head->next);
  node->random = copy_random_list_3(head->random);
  return node;
}

////////////////////////////////////////////////////////////////////////////////
// Helper function
void traverse(RandomListNode* head)
{
  while (head) {
    std::cout << head->label;
    std::cout << "(";

    if (head->random)
      std::cout << head->random->label;

    std::cout << ") -> ";

    head = head->next;
  }
  std::cout << "null" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  {
    RandomListNode *list{nullptr};
    RandomListNode *n1 = new RandomListNode(1);
    RandomListNode *n2 = new RandomListNode(2);
    RandomListNode *n3 = new RandomListNode(3);
    RandomListNode *n4 = new RandomListNode(4);
    RandomListNode *n5 = new RandomListNode(5);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

//    n1->random = n2;
//    n2->random = n3;
//    n3->random = n4;
//    n4->random = n5;

    list = n1;

    traverse(list);

    RandomListNode *new_list{nullptr};
//    new_list = copy_random_list(list);    // without hash table
//    new_list = copy_random_list_2(list);  // hash table without recursion
    new_list = copy_random_list_3(list);  // hash table with recursion

    traverse(new_list);
  }

  return 0;
}
