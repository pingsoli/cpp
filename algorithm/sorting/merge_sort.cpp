////////////////////////////////////////////////////////////////////////////////
//
// Merge sort - recursion implementation
// from http://simplestcodings.blogspot.com/2010/08/merge-sort-implementation-in-c.html
//
// Merge sort is table.
//
// Time Comeplexity:
// average: O(n log n)
//
// Requirements
// Need a copy of origin data.
//
// Example
//            0   1   2   3   4  5   6
// int a[] = {24, 56, 12, 34, 3, 78, 32}
//
// 0  3                        |
// 4  6                        |
// 0  3  6                     |
//
// 0  1    | 4  5              |
// 2  3    | 6  6              |
// 0  1  3 | 4  5  6           |
//
// 0  0    | 2  2    | 4  4    |
// 1  1    | 3  3    | 5  5    |
// 0  0  1 | 2  3  3 | 4  4  5 |
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

void merge(int*, int*, int, int, int);
void merge_sort(int *a, int *b, int low, int high)
{
  if (low < high) {
    int pivot = (low + high) / 2;
    merge_sort(a, b, low, pivot);
    merge_sort(a, b, pivot + 1, high);
    merge(a, b, low, pivot, high);
  }
}

void merge(int *a, int *b, int low, int pivot, int high)
{
  int h{low}, i{low}, j{pivot+1};

  while ((h<=pivot) && (j<=high))
    b[i++] = (a[h] <= a[j] ? a[h++] : a[j++]);

  int start = (h > pivot) ? j : h;
  int end   = (h > pivot) ? high : pivot;
  for (; start <= end; ++start) b[i++] = a[start];

  // copy data to array b
  for (int k = low; k <= high; ++k) a[k] = b[k];
}

void print(int *a, int size, const std::string& msg)
{
  std::cout << '\n' << msg << std::endl;
  for (int i = 0; i < size; ++i)
    std::cout << a[i] << ' ';
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
//  int a[] = {12, 10, 43, 23, -78, 45, 123, 56, 98, 41, 90, 24};
  int a[] = {24, 56, 12, 34, 3, 78, 32};
  int num = sizeof(a) / sizeof(int);
  int b[num];

  print(a, num, "before sorting");

  merge_sort(a, b, 0, num-1);

  print(a, num, "after sorting");
  print(b, num, "after sorting");

  return 0;
}
