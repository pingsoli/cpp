#include <cstddef>
#include <cstdlib>

#include <iostream>
#include <iterator>
#include <string>
#include <utility>

#include <boost/coroutine2/all.hpp>

struct node
{
  typedef std::shared_ptr<node> ptr_t;

  ptr_t left, right;
  std::string value;

  // construct leaf
  node(const std::string& v)
    : left{}, right{}, value{v}
  {}

  // construct non-leaf
  node(ptr_t l, const std::string& v, ptr_t r)
    : left{l}, right{r}, value{v}
  {}

  static ptr_t create(const std::string& v)
  {
    return ptr_t(new node(v));
  }

  static ptr_t create(ptr_t l, const std::string& v, ptr_t r)
  {
    return ptr_t(new node(l, v, r));
  }
};

node::ptr_t create_left_tree_from(const std::string& root)
{
  /* -----------
        root
        /  \
       b    e
      / \
     a   c
  ------------ */

  return node::create(
      node::create(
        node::create("a"),
        "b",
        node::create("c")),
      root,
      node::create("e")
    );
}

node::ptr_t create_right_tree_from(const std::string& root)
{
/* -----------
      root
      /  \
     a    d
         / \
        c   e
  ------------ */
  return node::create(
    node::create("a"),
    root,
    node::create(
      node::create("c"),
      "d",
      node::create("e"))
  );
}

// recursively walk the tree, delivery values in order
void traverse(node::ptr_t n, 
       boost::coroutines2::coroutine<std::string>::push_type& out)
{
  if (n->left)
    traverse(n->left, out);

  out(n->value);

  if (n->right)
    traverse(n->right, out);
}

int main()
{
  node::ptr_t left_d(create_left_tree_from("d"));
  node::ptr_t right_b(create_right_tree_from("b"));
  node::ptr_t right_x(create_right_tree_from("x"));

  typedef boost::coroutines2::coroutine<std::string> coro_t;
  {
    coro_t::pull_type left_d_reader(
      [&](coro_t::push_type& out) {
        traverse(left_d, out);
      });
    std::cout << "left tree from: d\n";
    std::copy(begin(left_d_reader),
              end(left_d_reader),
              std::ostream_iterator<std::string>(std::cout << " "));
    std::cout << std::endl;

    coro_t::pull_type right_b_reader(
        [&](coro_t::push_type& out) {
        traverse(right_b, out);
        });
    std::cout << "right tree from: b\n";
    std::copy(begin(right_b_reader),
              end(right_b_reader),
              std::ostream_iterator<std::string>(std::cout << " "));
    std::cout << std::endl;

    coro_t::pull_type right_x_reader(
        [&](coro_t::push_type& out) {
        traverse(right_x, out);
        });
    std::cout << "right tree form: x\n";
    std::copy(begin(right_x_reader),
              end(right_x_reader),
              std::ostream_iterator<std::string>(std::cout << " "));
    std::cout << std::endl;
  }

  {
    node::ptr_t left_d(create_left_tree_from("d"));
    node::ptr_t right_b(create_right_tree_from("b"));
    {
      coro_t::pull_type left_d_reader(
        [&](coro_t::push_type& out) {
        traverse(left_d, out);
        });

      coro_t::pull_type right_b_reader(
        [&](coro_t::push_type& out) {
        traverse(right_b, out);
        });

      std::cout << "left tree from d == right tree from b ? "
        << std::boolalpha
        << std::equal(begin(left_d_reader),
                      end(left_d_reader),
                      begin(right_b_reader))
        << std::endl;
    }
  }

  {
    node::ptr_t left_d(create_left_tree_from("d"));
    node::ptr_t right_x(create_right_tree_from("x"));
    {
      coro_t::pull_type left_d_reader(
        [&](coro_t::push_type& out) {
        traverse(left_d, out);
        });

      coro_t::pull_type right_x_reader(
        [&](coro_t::push_type& out) {
        traverse(right_x, out);
        });

      std::cout << "left tree from d == right tree from x ? "
        << std::boolalpha
        << std::equal(begin(left_d_reader),
                      end(left_d_reader),
                      begin(right_x_reader))
        << std::endl;
    }
  }

  std::cout << "Done!\n";
  return EXIT_SUCCESS;
}
