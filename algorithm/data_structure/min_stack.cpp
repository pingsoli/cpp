////////////////////////////////////////////////////////////////////////////////
//
// Min Stack
// from https://leetcode.com/problems/min-stack/description/
//
// Description
// Design a stack that supports push, pop, top, and retrieving the minimum
// element in contant time.
//
// 1) push(x)  -- Push element x onto stack
// 2) pop()    -- Removes the element on top of the stack
// 3) top()    -- Get the top element
// 3) getMin() -- Retrieve the minimum element in the stack
//
// Example
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin();  // returns -3
// minStack.pop();
// minStack.pop();     // return 0
// minStack.getMin();  // return -2
//
// References
// [1] https://stackoverflow.com/questions/3435926/insert-delete-max-in-o1
//
// Solution
// So for example, after pushing 1,2,3,4,5 onto the stack, your stacks would look like this:
// MAIN   MIN
// +---+  +---+
// | 5 |  | 1 |
// | 4 |  | 1 |
// | 3 |  | 1 |
// | 2 |  | 1 |
// | 1 |  | 1 |
// +---+  +---+
// However, if you were to push 5,4,3,2,1, the stacks would look like this:
//
// MAIN   MIN
// +---+  +---+
// | 1 |  | 1 |
// | 2 |  | 2 |
// | 3 |  | 3 |
// | 4 |  | 4 |
// | 5 |  | 5 |
// +---+  +---+
// For 5,2,4,3,1 you would have:
//
// MAIN   MIN
// +---+  +---+
// | 1 |  | 1 |
// | 3 |  | 2 |
// | 4 |  | 2 |
// | 2 |  | 2 |
// | 5 |  | 5 |
// +---+  +---+
// and so on.
//
// You can also save some space by pushing to the min stack only when the
// minimum element changes, iff the items are known to be distinct.
//
////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <iostream>
#include <vector>

struct MinStack {
  std::vector<int> data_stack;
  std::vector<int> min_stack;

  void push(int val) {
    data_stack.push_back(val);

    if (min_stack.empty()) {
      min_stack.push_back(val);
      return;
    }

    int min = (val < min_stack.back() ? val : min_stack.back());
    min_stack.push_back(min);
  }

  int pop() {
    if (data_stack.empty()) return INT_MIN;
    min_stack.pop_back();
    int ret = data_stack.back();
    data_stack.pop_back();
    return ret;
  }

  int get_min() {
    return min_stack.back();
  }

  int top() {
    return data_stack.back();
  }
};

int main(int argc, char** argv)
{
  MinStack min_stack;

  min_stack.push(-2);
  min_stack.push(0);
  min_stack.push(-3);

  std::cout << "min:" << min_stack.get_min() << std::endl;
  std::cout << "pop:" << min_stack.pop() << std::endl;
  std::cout << "pop:" << min_stack.pop() << std::endl;
  std::cout << "min:" << min_stack.get_min() << std::endl;

  return 0;
}
