#include <string>
#include <iterator>
#include <iostream>
#include <vector>

#include "pimpl.h"

struct Widget::Impl
{
  std::string name_;
  std::vector<double> data_;

  void setName(const std::string& name) {
    name_ = name;
  }

  std::string getName() const {
    return name_;
  }

  void addData(std::initializer_list<double> ld) {
    data_ = ld;
  }

  void showData() const {
    std::copy(data_.begin(), data_.end(),
        std::ostream_iterator<double>(std::cout, "\t"));
    std::cout << '\n';
  }
};

Widget::Widget() :
  pImpl(std::make_unique<Impl>())
{}

Widget::~Widget() = default;

// copy operations implementation
Widget::Widget(const Widget& rhs)
  : pImpl(std::make_unique<Impl>(*rhs.pImpl))
{}

Widget& Widget::operator=(const Widget& rhs) {
  *pImpl = *rhs.pImpl;
  return *this;
}

// move operations
Widget::Widget(Widget&& rhs) = default;
Widget& Widget::operator=(Widget&& rhs) = default;

void Widget::setName(const std::string& name) {
  pImpl->setName(name);
}

std::string Widget::getName() const {
  return pImpl->getName();
}

void Widget::addData(std::initializer_list<double> ld) {
  pImpl->addData(ld);
}

void Widget::showData() const {
  pImpl->showData();
}
