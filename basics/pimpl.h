// pimpl idiom: point to implementation
// reduce the build times.
// copy data cost too much time.

#pragma once

#include <string>
#include <memory>
#include <initializer_list>

class Widget
{
public:
  Widget();
  ~Widget();

  Widget(const Widget& rhs);
  Widget& operator=(const Widget& rhs);

  Widget(Widget&& rhs);
  Widget& operator=(Widget&& rhs);

  void setName(const std::string&);
  std::string getName() const;
  void addData(std::initializer_list<double>);
  void showData() const;

private:
  struct Impl;
  std::unique_ptr<Impl> pImpl;
};
