///////////////////////////////////////////////////////////////////////////////
//
// Binary Search
//
// Precondition: the array must be sorted
// cut search space in half after each comparison
// log2(N)
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

int binary_search(int array[], int length, int search_value)
{
  int low = 0;
  int high = length - 1;
  int mid;

  while (low <= high)
  {
    mid = (low + high) / 2;

    std::cout << low << ' ' << mid << ' ' << high << std::endl;

    if (search_value == array[mid])
    {
      return mid;
    }
    else if (search_value < array[mid])
    {
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }
  return -1;
}

int main(int argc, char** argv)
{
  int a[] = { 11, 22, 33, 44, 55, 66, 77, 88 };
  int search_value;

  std::cout << "the array: ";
  for (int i = 0; i < 8; ++i)
    std::cout << a[i] << ' ';
  std::cout << std::endl;

  std::cout << "Enter the value you want to search: ";
  std::cin >> search_value;

  int index = binary_search(a, 8, search_value);

  if (index >= 0)
  {
    std::cout << "Found the " << search_value << "!\n"
              << "the index of array is: " << index << std::endl;
  }
  else
  {
    std::cout << "Not found!" << std::endl;
  }

  return 0;
}
