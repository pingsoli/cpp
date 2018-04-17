#include <iostream>

struct Node {
  int     data;
  Node* left;
  Node* right;

  Node(int data_) :
    data{data_},
    left{nullptr},
    right{nullptr}
  {}
};

class BST {
private:
  Node* root;

  void make_empty(Node* t)
  {
    if (t == nullptr)
      return;

    make_empty(t->left);
    make_empty(t->right);
    delete t;

    return;
  }

  Node* insert(int data_, Node* t)
  {
    if (t == nullptr)
      t = new Node(data_);
    else if (data_ < t->data)
      t->left = insert(data_, t->left);
    else if (data_ > t->data)
      t->right = insert(data_, t->right);

    return t;
  }

  Node* remove(int data_, Node* t)
  {
    Node* tmp;

    if (t == nullptr)
      return nullptr;
    else if (data_ < t->data)
      t->left = remove(data_, t->left);
    else if (data_ > t->data)
      t->right = remove(data_, t->right);
    else if (t->left && t->right)
    {
      tmp = find_min(t->right);
      t->data = tmp->data;
      t->right = remove(t->data, t->right);
    }
    else
    {
      tmp = t;
      if (t->left == nullptr)
        t = t->right;
      else if (t->right == nullptr)
        t = t->left;
      delete tmp;
    }

    return t;
  }

  Node* find_min(Node* t)
  {
    if (t == nullptr)
      return nullptr;
    else if (t->left == nullptr)
      return t;
    else
      return find_min(t->left);
  }

  Node* find_max(Node* t)
  {
    if (t == nullptr)
      return nullptr;
    else if (t->right == nullptr)
      return t;
    else
      return find_max(t->right);
  }

  Node* find(Node* t, int data_)
  {
    if (t == nullptr)
      return nullptr;
    else if (data_ < t->data)
      return find(t->left, data_);
    else if (data_ > t->data)
      return find(t->right, data_);
    else
      return t;
  }

public:
  BST() : root{nullptr} {}

  ~BST() {
    make_empty(root);
  }

  void insert(int data_) {
    root = insert(data_, root);
  }

  void remove(int data_) {
    root = remove(data_, root);
  }

  Node* search(int data_) {
    return find(root, data_);
  }

  const Node* get_root() const {
    return root;
  }
};

void preorder(const Node* const root)
{
  if (root == nullptr)
    return;

  std::cout << root->data << ' ';
  preorder(root->left);
  preorder(root->right);
}

void inorder(const Node* const root)
{
  if (root == nullptr)
    return;

  inorder(root->left);
  std::cout << root->data << ' ';
  inorder(root->right);
}

void postorder(const Node* const root)
{
  if (root == nullptr)
    return;

  postorder(root->left);
  postorder(root->right);
  std::cout << root->data << ' ';
}

void traverse(const Node* node)
{
  std::cout << "preorder:  ";
  preorder(node);
  std::cout << std::endl;

  std::cout << "inorder:   ";
  inorder(node);
  std::cout << std::endl;

  std::cout << "postorder: ";
  postorder(node);
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //               50
  //           /        \
  //         /            \
  //       40              60
  //     /   \           /    \
  //   35     45       55     70
  //  /  \   /  \     /  \   /  \
  // 30  38 43  48   52  58 68  72

  BST t;

  t.insert(50);
  t.insert(40);
  t.insert(60);
  t.insert(35);
  t.insert(45);
  t.insert(55);
  t.insert(70);
  t.insert(30);
  t.insert(38);
  t.insert(43);
  t.insert(48);
  t.insert(52);
  t.insert(58);
  t.insert(68);
  t.insert(72);

  traverse(t.get_root());

  std::cout << "\nremoving 40 ...." << std::endl;
  t.remove(40);
  traverse(t.get_root());

  std::cout << "\nremoving 30 ...." << std::endl;
  t.remove(30);
  traverse(t.get_root());

  std::cout << "\nfinding 60 ...." << std::endl;
  Node* found = t.search(60);
  std::cout << "traversing found node 60 ...." << std::endl;
  traverse(found);

  /////////////////////////////////////////////////////////////////////////////
  // preorder:  A B C
  // postorder: C B A
  //
  // we don't know B > C or B < C.
  //     A              A
  //    /              /
  //   B      or      B
  //  /                \
  // C                  C

  BST t1;

  t1.insert(30);
  t1.insert(20);
  t1.insert(10);

  std::cout << std::endl;
  traverse(t1.get_root());

  BST t2;

  t2.insert(30);
  t2.insert(20);
  t2.insert(25);

  std::cout << std::endl;
  traverse(t2.get_root());
  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
