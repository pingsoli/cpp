///////////////////////////////////////////////////////////////////////////////
//
// functor
//
// References
// [1] https://www.quantstart.com/articles/Function-Objects-Functors-in-C-Part-1
// [2] http://jackieokay.com/2017/01/26/functors.html
// [3] https://my.oschina.net/llehs/blog/180594/
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>  // std::shared_ptr

///////////////////////////////////////////////////////////////////////////////

struct BinaryFunction
{
  virtual double operator()(double left, double right) = 0;
};

class Add : public BinaryFunction
{
  virtual double operator()(double left, double right)
  { return left + right; }
};

class Multiply : public BinaryFunction
{
  virtual double operator()(double left, double right)
  { return left * right; }
};

double binary_op(double left, double right, BinaryFunction* func)
{
  return (*func)(left, right);
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  double a = 5.0;
  double b = 10.0;

  std::shared_ptr<BinaryFunction> pAdd(new Add);
  std::shared_ptr<BinaryFunction> pMul(new Multiply);

  std::cout << "Add: " << binary_op(a, b, pAdd.get())<< std::endl;
  std::cout << "Multiply: " << binary_op(a, b, pMul.get()) << std::endl;

  return 0;
}
