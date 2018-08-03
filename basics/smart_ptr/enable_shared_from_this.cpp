#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

class Widget;
std::vector<std::shared_ptr<Widget>> processWidgets;

class Widget : public std::enable_shared_from_this<Widget>
{
public:
  std::shared_ptr<Widget> f() {
    // use raw pointer, what will happen ?
    // return std::shared_ptr<Widget>(this);

    // the following two has the same effect.
    // return shared_from_this();
    return std::shared_ptr<Widget>(shared_from_this());
  }

  void process() {
    // processWidgets.emplace_back(this); // add it to list of processed widgets,
                                       // this is wrong!
    // this behavior will create new control block for pointed-to Widget(*this).
    // if there are std::shared_ptrs outside the member function that already
    // point to that Widget. It's undefined behavior.

    // shared_from_this looks up the control block for the current object.
    // and it creates a new std::shared_ptr that refers to that control block.
    processWidgets.emplace_back(shared_from_this());
  }
};

int main(int argc, char *argv[])
{
  using WidgetPtr = std::shared_ptr<Widget>;

  {
    // enable_shared_from_this
    WidgetPtr p(new Widget); // construct shared_ptr and control block, the
    // ref-count is 1.
    WidgetPtr q(p->f()); // to make the new pointer point to same place.
    // the ref-count shoule be 2.
    // but if you use `return std::shared_ptr<Widget>(this)`
    // the ref-count will be still 1.
    // what happened ?

    p.reset(); // p's ref-count is zero, the resource will not be release instantly.
               // maybe other shared_ptr 'owns' the resource.

    std::cout << "p use count: " << p.use_count() << '\n';
    std::cout << "q use count: " << q.use_count() << '\n';
  }

  {
    // deleting the pointer twice will cause undefined behavior.
    // use raw pointer to initialize std::shared_ptr
    auto wptr = new Widget;
    auto deleter = [] (Widget* w) {
      // do something, like logging.
      std::cout << "deleter called" << '\n';
      std::cout << "deleting address: " << w << '\n';
      delete w;
    };

    WidgetPtr spw1(wptr, deleter); // create control block for *wptr
    WidgetPtr spw2(wptr, deleter); // create 2nd control block for *wptr
    // so the wptr will deleted twice, it's undefined behavior.

    std::cout << "spw1 use count: " << spw1.use_count() << '\n';
    std::cout << "spw2 use count: " << spw2.use_count() << '\n';
  }

  return 0;
}
