////////////////////////////////////////////////////////////////////////////////
//
// Question
// Given a binary tree, how will you find its maximum width ?
//
// Solution
// We can use level order traversal along with queue to find maximum width.
// BFS
//
////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <iostream>

struct BinaryTreeNode {
  int val;
  BinaryTreeNode *left, *right;

  BinaryTreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
};

int max_width(BinaryTreeNode *node)
{
  if (!node) return 0;

  std::queue<BinaryTreeNode*> nodes_queue;
  int max{0}; // record max_width

  nodes_queue.push(node);  // push root node

  while (!nodes_queue.empty()) {
    max = (max < nodes_queue.size()) ? nodes_queue.size() : max;

    BinaryTreeNode *n = nodes_queue.front();
    nodes_queue.pop();

    if (n->left)  nodes_queue.push(n->left);
    if (n->right) nodes_queue.push(n->right);
  }

  return max;
}

int main(int argc, char** argv)
{
  //     root    |     1
  //    /    \   |    / \
  //   n1    n2  |   2   5
  //  /  \    \  |  / \   \
  // n3  n4   n5 | 3   4   7

  BinaryTreeNode *root = new BinaryTreeNode(1);
  BinaryTreeNode *n1   = new BinaryTreeNode(2);
  BinaryTreeNode *n2   = new BinaryTreeNode(5);
  BinaryTreeNode *n3   = new BinaryTreeNode(3);
  BinaryTreeNode *n4   = new BinaryTreeNode(4);
  BinaryTreeNode *n5   = new BinaryTreeNode(7);

  BinaryTreeNode *n6 = new BinaryTreeNode(8);  // add new node

  root->left  = n1;
  root->right = n2;
  n1->left    = n3;
  n1->right   = n4;
  n2->right   = n5;

  n2->left = n6;  // add new node

  std::cout << "current max width: " << max_width(root) << std::endl;
  return 0;
}
