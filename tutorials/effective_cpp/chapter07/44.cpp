///////////////////////////////////////////////////////////////////////////////
//
// Item 44: Factor parameter-independent code out of templates
//
// Things to remember
//
// 1) Templates generate multiple classes and multiple functions, so any
// template code not dependent on a template parameter causes bloat.
//
// 2) Bloat due to non-type template parameters can often be eliminated by
// replacing template parameters with function parameters or class data
// members.
//
// 3) Bloat due to type parameters can be reduced by sharing implementations
// for instantiation types with identical binary representations.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

template <typename T>
class SquareMatrixBase {
protected:
  SquareMatrixBase(std::size_t n, T* pMem)
    : size(n), pData(pMem) {}

  void setDatePtr(T* ptr) { pData = ptr; }

  void invert(std::size_t matrix_size)
  {
    std::cout << "hahhahah" << std::endl;
    std::cout << "big surprise" << std::endl;
  }

private:
  std::size_t size;
  T* pData;
};

template <typename T, std::size_t n>
class SquareMatrix : public SquareMatrixBase<T> {

  using SquareMatrixBase<T>::invert;

public:
  SquareMatrix()
    : SquareMatrixBase<T>(n, data) {}

  void invert() { this->invert(n); }

private:
  T data[n * n];
};

int main(int argc, char** argv)
{
  SquareMatrix<float, 10> sm;
  sm.invert();

  return 0;
}
