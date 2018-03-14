///////////////////////////////////////////////////////////////////////////////
//
// Item 42: Understand the two meanings of typename.
//
///////////////////////////////////////////////////////////////////////////////
//
// Things to remember
// 1) When declaring template parameters, class and typename are
// interchangeable.
//
// 2) Use typename to identify nested dependent type names, except in base
// classes lists or as a base class identifier in a member initialization list
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <iterator>

///////////////////////////////////////////////////////////////////////////////
//
// Anytime you refer to a nested dependent type name in a template, you must
// immediately precede it by the word typename.
//
template <typename C>
void print2nd(const C& container)
{
  if (container.size() >= 2)
  {
    typename C::const_iterator iter(container.begin());
    std::cout << *(++iter) << std::endl;
  }
}

template <typename C>
void print2nd(const C& container, typename C::const_iterator iter)
{
  if (container.size() >= 2)
    std::cout << *(++iter) << std::endl;
}

// use std::next
// template <typename IterT>
// void print2nd(const IterT iter)
// {
//   std::cout << *next(iter, 2) << std::endl;
// }

///////////////////////////////////////////////////////////////////////////////

template <typename IterT>
void workWithIterator(IterT iter)
{
  typedef typename std::iterator_traits<IterT>::value_type value_type;

  value_type temp(*iter);
  std::cout << temp << std::endl;
}

template <typename IterT>
void traverse(IterT begin, IterT end)
{
  for (IterT iter = begin; iter != end; ++iter)
    std::cout << *iter << ' ';
  std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv)
{
  std::vector<int> v = { 1, 2, 3, 4, 5, 6 };

  // empty the vector, and release the memory
  v.clear();
  std::vector<int> empty_int_vector;
  v.swap(empty_int_vector);

//  std::cout << v.size() << std::endl;

  print2nd<std::vector<int>>(v);
  print2nd<std::vector<int>>(v, v.cbegin());
//  print2nd<std::vector<int>::const_iterator>(v.cbegin());

//  workWithIterator<std::vector<int>::const_iterator>(v.cbegin());
  traverse<std::vector<int>::const_iterator>(v.cbegin(), v.cend());

  return 0;
}
