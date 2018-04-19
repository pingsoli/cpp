////////////////////////////////////////////////////////////////////////////////
//
// Question
// Given a Binary tree, how will you find the Vertical Sum of binary tree ?
//
// 1 2  3  4 5
// | |  |  | |
//      1
//    /   \
//   2     3
//  /  \  / \
// 4    5/   6
//      7
//
// Example
// for the binary tree has 5 vertical lines.
// For line 3 the sum will be: 3 + 5 + 7 = 13
//
// Solution
// we need to check the Horizontal Distance (HD) from root for all nodes.
// The idea is simple.
//
// HD for root is 0.
//
// For right child we will +1 (add 1) to HD
// For left child we will -1 (subtract 1) from HD
//
//       0
//       1
//  -1 /   \ 1
//    2     3
//-2 /  \0 / \  2
//  4    5/   6
//       7
//       0
//
// we can easily maintain a hash map for horizontal distance corresponding to
// each vertial line.
//
// After traversal we will have following map
// +---------------------+-----+
// | Horizontal Distance | Sum |
// |          -2         | 4   |
// |          -1         | 2   |
// |           0         | 13  |
// |           1         | 3   |
// |           2         | 6   |
// +---------------------+-----+
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <map>

#define PINGSOLI_DEBUG 1

struct TreeNode {
  int val;
  TreeNode *left, *right;

  TreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
};

std::map<int, int> map;

void traverse(TreeNode*, int);
int vertical_sum(TreeNode *root, int column)
{
  traverse(root, 0);
#if PINGSOLI_DEBUG
  for (auto& it : map)
    std::cout << it.first << ' ' << it.second << std::endl;
#endif
  return std::next(begin(map), column-1)->second;
}

void traverse(TreeNode* node, int current_column)
{
  if (node) {
    map[current_column] += node->val;
    traverse(node->left, current_column-1);
    traverse(node->right, current_column+1);
  }
}

int main(int argc, char** argv)
{
  {
    //     root           1
    //    /    \        /   \
    //   n1    n4      2     3
    //  /  \   / \    /  \  / \
    // n2  n3 /  n6  4    5/   6
    //       n5           7
    // prepare data
    TreeNode *root = new TreeNode(1);
    TreeNode *n1 = new TreeNode(2);
    TreeNode *n2 = new TreeNode(4);
    TreeNode *n3 = new TreeNode(5);
    TreeNode *n4 = new TreeNode(3);
    TreeNode *n5 = new TreeNode(7);
    TreeNode *n6 = new TreeNode(6);

    root->left = n1;
    root->right = n4;
    n1->left = n2;
    n1->right = n3;
    n4->left = n5;
    n4->right = n6;

    int column = 3;
    std::cout << "line " << column << " sum: "
      << vertical_sum(root, column) << std::endl;
  }

  return 0;
}
