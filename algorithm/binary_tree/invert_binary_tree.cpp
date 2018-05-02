////////////////////////////////////////////////////////////////////////////////
//
// Invert binary tree
// from https://leetcode.com/problems/invert-binary-tree/description/
//
// Description
//      4
//    /   \
//   2     7
//  / \   / \
// 1   3 6   9
//
// to
//      4
//    /   \
//   7     2
//  / \   / \
// 9   6 3   1
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <queue>
#include <stack>

struct TreeNode {
  int val;
  TreeNode *left, *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

////////////////////////////////////////////////////////////////////////////////
// recursive solution
TreeNode *invert_tree(TreeNode *root) {
  if (root) {
    invert_tree(root->left);
    invert_tree(root->right);
    std::swap(root->left, root->right);
  }
  return root;
}

////////////////////////////////////////////////////////////////////////////////
// non-recursive solution

TreeNode *invert_tree_1(TreeNode *root) {
  std::stack<TreeNode*> stk;
  stk.push(root);

  while (!stk.empty()) {
    TreeNode *p = stk.top();
    stk.pop();
    if (p) {
      stk.push(p->left);
      stk.push(p->right);
      std::swap(p->left, p->right);
    }
  }
  return root;
}
////////////////////////////////////////////////////////////////////////////////
// level traverse
std::vector<std::vector<int>> ret;
void build_vector(TreeNode *root, int depth) {
  if (!root) return;
  if (ret.size() == depth)
    ret.push_back(std::vector<int>());

  ret[depth].push_back(root->val);
  build_vector(root->left, depth + 1);
  build_vector(root->right, depth + 1);
}

void level_traverse(TreeNode *root) {
  build_vector(root, 0);

  for (int i = 0; i < ret.size(); ++i)
  {
    for (int j = 0; j < ret[i].size(); ++j)
      std::cout << ret[i][j] << ' ';
    std::cout << std::endl;
  }

  ret.clear();
}

int main(int argc, char** argv)
{
  {
    //     root
    //    /    \
    //   n1     n2
    //  /  \   /  \
    // n3  n4 n5  n6
    TreeNode *root = new TreeNode(4);
    TreeNode *n1 = new TreeNode(2);
    TreeNode *n2 = new TreeNode(7);
    TreeNode *n3 = new TreeNode(1);
    TreeNode *n4 = new TreeNode(3);
    TreeNode *n5 = new TreeNode(6);
    TreeNode *n6 = new TreeNode(9);

    root->left  = n1;
    root->right = n2;
    n1->left    = n3;
    n1->right   = n4;
    n2->left    = n5;
    n2->right   = n6;

    level_traverse(root);
    invert_tree(root);
    level_traverse(root);
  }
  return 0;
}
