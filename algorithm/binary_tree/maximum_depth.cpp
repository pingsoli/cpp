////////////////////////////////////////////////////////////////////////////////
//
// Maximum depth of binary tree
// from https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
//
// Description
// Given a binary tree, find its maximum depth.
//
// the maximum depth is the number of nodes along path from the root node down
// to the farthest leaf node.
//
// NOTE: A leaf is a node with no children.
//
// Example
// Given a binary tree [3, 9, 20, null, null, 15, 7]
//   3
//  / \
// 9  20
//   /  \
//  15   7
//
// Solution
// 1) recursion
// 2) stack
// 3) dfs
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <stack>

struct BinaryTreeNode {
  int val;
  BinaryTreeNode *left, *right;

  BinaryTreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
};

////////////////////////////////////////////////////////////////////////////////
// recursive solution
int max_depth(BinaryTreeNode *node)
{
  if (!node) return 0;

  int left_depth  = max_depth(node->left);
  int right_depth = max_depth(node->right);

  return std::max(left_depth, right_depth) + 1;
}
////////////////////////////////////////////////////////////////////////////////
// without recursion using stack
int max_depth_1(BinaryTreeNode *node)
{
  if (!node) return 0;

  std::stack<BinaryTreeNode*> stack;
  BinaryTreeNode *curr{nullptr}, *prev{nullptr};
  int max_depth{0};
  stack.push(node);

  while (!stack.empty()) {
    curr = stack.top();

    if (!prev || prev->left == curr || prev->right == curr) {
      if (curr->left) {
        stack.push(curr->left);
      } else if (curr->right) {
        stack.push(curr->right);
      }
    } else if (curr->left == prev) {
      if (curr->right)
        stack.push(curr->right);
    } else {
      stack.pop();
    }

    prev = curr;
    max_depth = (max_depth > stack.size() ? max_depth : stack.size());
  }
  return max_depth;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  //   3     |  root
  //  / \    |  /  \
  // 9  20   | n1  n2
  //   /  \  |     / \
  //  15   7 |    n3 n4

  BinaryTreeNode *root = new BinaryTreeNode(3);
  BinaryTreeNode *n1   = new BinaryTreeNode(9);
  BinaryTreeNode *n2   = new BinaryTreeNode(20);
  BinaryTreeNode *n3   = new BinaryTreeNode(15);
  BinaryTreeNode *n4   = new BinaryTreeNode(7);

  BinaryTreeNode *n5 = new BinaryTreeNode(30); // add new node

  root->left  = n1;
  root->right = n2;
  n2->left    = n3;
  n2->right   = n4;

  n3->left = n5;  // add n5 to n3 as left child

  std::cout << "max depth: " << max_depth(root) << std::endl;
  std::cout << "max depth: " << max_depth_1(root) << std::endl;

  return 0;
}

