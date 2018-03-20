///////////////////////////////////////////////////////////////////////////////
//
// std::vector
//
// How the std::vectors grow ?
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <new>
#include <vector>
#include <iostream>

template <typename Tp>
struct NAlloc {
  typedef Tp value_type;
  NAlloc() = default;

  template <typename T> NAlloc(const NAlloc<T>&) {}
  Tp* allocate(std::size_t n) {
    n *= sizeof(Tp);
    std::cout << "allocating " << n << " bytes\n";
    return static_cast<Tp*>(::operator new(n));

  }

  void deallocate(Tp* p, std::size_t n) {
    std::cout << "deallocating " << n*sizeof*p << " bytes\n";
    ::operator delete(p);
  }
};

template <typename T, typename U>
bool operator==(const NAlloc<T>&, const NAlloc<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const NAlloc<T>&, const NAlloc<U>&) { return false; }

struct test {
//  test(int i = 0, double d = 0.0)
//    : i_{i}, d_{d} {}

  test(int i = 0, char c = 0)
    : i_{i}, c_{c}
  {}

  char c_;
  int i_;
};

template <typename T>
void fill_vector_with_preallocation(std::size_t sz)
{
  std::vector<T, NAlloc<T>> v1;
  v1.reserve(sz);

  for (int n = 0; n < sz; ++n)
    v1.emplace_back(n);
}

template <typename T>
void fill_vector_without_preallocation(std::size_t sz)
{
  std::vector<T, NAlloc<T>> v1;

  for (int n = 0; n < sz; ++n)
    v1.emplace_back(n);
}

int main(int argc, char** argv)
{
  int sz = 100;

  std::cout << "using reserve: \n";
  fill_vector_with_preallocation<test>(100);
//  fill_vector_with_preallocation<int>(100);

  std::cout << "not using reserve: \n";
  fill_vector_without_preallocation<test>(100);
// fill_vector_without_preallocation<int>(100);

  return 0;
}
