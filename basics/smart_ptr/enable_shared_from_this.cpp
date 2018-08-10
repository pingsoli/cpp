////////////////////////////////////////////////////////////////////////////////
// why inherit std::enable_shared_from_this ?
// because we want get the shared_ptr from the object memthod.
//
// If you want to know why use enable_shared_from_this and shared_from_this.
// you must clear about control block and data of shared_ptr.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Widget;
// global widgets manager
std::vector<std::shared_ptr<Widget>> processWidgets;

class Widget : public std::enable_shared_from_this<Widget>
{
public:
  Widget(const std::string& name_) : name(name_) {}

  void process() {
    // Good
    // shared_from_this looks up the control block for the current object.
    // and it creates a new std::shared_ptr that refers to that control block.
    processWidgets.emplace_back(shared_from_this());

    // Bad
    // processWidgets.emplace_back(this);
  }

  std::shared_ptr<Widget> getPtr() {
    // return shared_from_this(); // Good
    return std::shared_ptr<Widget>(this); // Bad
  }

  // testing interface
  std::string getName() const {
    return name;
  }

private:
  std::string name;
};

int main(int argc, char *argv[])
{
  {
    // why shared_from_this()?

    // create a widget on heap memory through shared_ptr,
    // and push it to processWidgets.
    {
      auto widget = std::make_shared<Widget>("world");
      widget->process();
    } // leaving the scope, and widget's ref-count decrease 1.
      // if we use `processWidgets.emplace_back(this);`, widget's ref-count turns 0.
      // and the resource allocated on heap will be released.
      //
      // if we use `processWidgets.emplace_back(shared_from_this())`, we create
      // another shared pointer to point to the resource, and the ref-count is 1.
      // the resource won't be released.

    // now we fetch it from processWidgets.
    if (!processWidgets.empty())
      std::cout << processWidgets[0]->getName() << '\n';


    // another example, difference situation.
    std::shared_ptr<Widget> outer_ptr;
    {
      auto widget = std::make_shared<Widget>("new widget");
      outer_ptr = widget->getPtr(); // what happens ?

      // if we use `return shared_from_this();`, widget and outer_ptr will share
      // same control block, and outer_ptr's reference counts will be 2.
      // leaving the local scope, outer_ptr's ref-count decrease to 1, because
      // widet(shared_ptr) is local variable, and destructed(decrease the
      // control block's reference count).

      // if we use `return std::shared_ptr<Widget>(this);`, widget(shared_ptr)
      // and outer_ptr will have there own control block, but point to same
      // resource. widget(shared_ptr) and outer_ptr's reference count are both 1.
      // Because of widget is local variable, it's destructed when leaving
      // the scope(the ref-count turns 0), and the resource will be released.

      std::cout << "outer_ptr use_count: " << outer_ptr.use_count() << '\n';
    } // leaving the scope

    std::cout << "outer_ptr use_count: " << outer_ptr.use_count() << '\n';
    std::cout << outer_ptr->getName() << '\n';
  }

  // summary
  // if we don't use enable_shared_from_this and shared_from_this(),
  // we may use the deleted resource wrongly.
  // make use you return the shared_from_this() and use the shared_from_this()
  // in the member function.

  return 0;
}
