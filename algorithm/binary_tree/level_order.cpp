////////////////////////////////////////////////////////////////////////////////
//
// level order binary tree
// from https://leetcode.com/problems/binary-tree-level-order-traversal/description/
//
// Descrition
// Given a binary tree, return the level order traversal of its nodes' values. 
// (ie, from left to right, level by level).
//
// For example:
// Given binary tree [3,9,20,null,null,15,7],])
//    3
//   / \
//  9  20
//     / \
//    15  7
//
// returns its level order traversal as:
// [
//   [3],
//   [9, 20],
//   [15, 7],
// ]
//
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left, *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<int>> ret;

void build_vector(TreeNode *root, int depth)
{
  if (!root) return;
  if (ret.size() == depth)
    ret.push_back(std::vector<int>());

  ret[depth].push_back(root->val);
  build_vector(root->left, depth + 1);
  build_vector(root->right, depth + 1);
}

std::vector<std::vector<int>> level_order(TreeNode *root) {
  build_vector(root, 0);
  return ret;
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  TreeNode *root = new TreeNode(3);
  TreeNode *n1 = new TreeNode(9);
  TreeNode *n2 = new TreeNode(20);
  TreeNode *n3 = new TreeNode(15);
  TreeNode *n4 = new TreeNode(7);

  root->left  = n1;
  root->right = n2;
  n2->left    = n3;
  n2->right   = n4;

  std::vector<std::vector<int>> v = level_order(root);

  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
      std::cout << v[i][j] << ' ';
    std::cout << std::endl;
  }

  return 0;
}
