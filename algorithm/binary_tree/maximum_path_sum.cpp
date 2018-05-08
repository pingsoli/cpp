////////////////////////////////////////////////////////////////////////////////
//
// Maximum path sum
// from https://leetcode.com/problems/binary-tree-maximum-path-sum/description/
//
// Description
// Given a non-empty binary tree, find the maximum path sum.
//
// for this problem, a path is defined as any sequence of nodes from some
// starting node to any node in the tree along the parent-child connnections,
// The path must contain at least one node and does not need to go through the
// root.
//
//    1
//   / \
//  2   3
// output: 6 (2 + 1 + 3)
//
//   -10
//   /  \
//  9   20
//      / \
//     15  7
// output: 42 (15 + 20 + 7)
//
// Solution
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left, *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int max_path_sum(TreeNode *root) {

}

int main(int argc, char** argv)
{
  {

  }

  {

  }

  return 0;
}
