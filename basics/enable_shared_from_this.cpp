#include <iostream>
#include <memory>
#include <cassert>

class Y : public std::enable_shared_from_this<Y>
{
public:
  std::shared_ptr<Y> f() {
    return shared_from_this();
    // return std::shared_ptr<Y>(this);
  }
};

int main(int argc, char *argv[])
{
  std::shared_ptr<Y> p(new Y);
  std::shared_ptr<Y> q = p->f();
  assert(p == q);

  return 0;
}
