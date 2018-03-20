///////////////////////////////////////////////////////////////////////////////
//
// The interface to the std::stack container adapter
// it's not thread-safe.
//
///////////////////////////////////////////////////////////////////////////////

#include <deque>

template <typename T, typename Container = std::deque<T>>
class stack
{
public:
  explicit stack(const Container&);
  explicit stack(Container&& = Container());
  template <class Alloc> stack(const Container&, const Alloc&);
  template <class Alloc> stack(Container&&, const Alloc&);
  template <class Alloc> stack(stack&&, const Alloc&);

  bool empty() const;
  std::size_t size() const;
  T& top();
  T const& top() const;
  void push(T const&);
  void push(T&&);
  void pop();
  void swap(stack&&);
};

int main(int argc, char** argv)
{
  return 0;
}
