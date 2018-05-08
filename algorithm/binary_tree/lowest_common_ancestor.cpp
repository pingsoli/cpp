////////////////////////////////////////////////////////////////////////////////
//
// Lowest common ancestor
// from https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
//
// Description
// Given the root and two nodes in binary tree, find the lowest common ancestor
// (LCA) of the two nodes.
// the lowest common ancestor is the node with largest depth which is the
// ancestor of both nodes.
//
// Example
// For the following binary tree.
//
//   4
//  / \
// 3   7
//    / \
//   5   6
// LCA(3, 5) = 4
// LCA(5, 6) = 7
// LCA(6, 7) = 7
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left, *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

////////////////////////////////////////////////////////////////////////////////
// bottom-up recursive solution
TreeNode *lowest_common_ancestor(TreeNode *root, TreeNode *A, TreeNode *B)
{
  // return either A or B or nullptr
  if (!root || root == A || root == B) return root;

  TreeNode *left  = lowest_common_ancestor(root->left, A, B);
  TreeNode *right = lowest_common_ancestor(root->right, A, B);

  // A and B on both side
  if (left && right) return root;

  // either left or right or nullptr
  return (left ? left : right);
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  {
    //      4      |     root
    //    /   \    |    /    \
    //   3     7   |   n1    n2
    //  / \   / \  |  /  \   / \
    // 1   2 5   6 | n3  n4 n5 n6
    TreeNode *root = new TreeNode(4);
    TreeNode *n1 = new TreeNode(3);
    TreeNode *n2 = new TreeNode(7);
    TreeNode *n3 = new TreeNode(1);
    TreeNode *n4 = new TreeNode(2);
    TreeNode *n5 = new TreeNode(5);
    TreeNode *n6 = new TreeNode(6);

    root->left  = n1;
    root->right = n2;
    n1->left    = n3;
    n1->right   = n4;
    n2->left    = n5;
    n3->right   = n6;

    TreeNode *a = n5;
    TreeNode *b = n6;
    TreeNode *ret = nullptr;

    // It's kind of wired when traverse the last node
    ret = lowest_common_ancestor(root, a, b);

    std::cout << "lowest common ancestor: " << ret->val << std::endl;
  }

  return 0;
}
