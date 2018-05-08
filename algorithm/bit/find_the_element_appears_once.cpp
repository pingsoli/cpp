////////////////////////////////////////////////////////////////////////////////
//
// Find the element that appears once
// fromhttps://www.geeksforgeeks.org/find-the-element-that-appears-once/
//
// Description
// Given an array where every element occurs tree times, except one element
// which occurs only once. Find the element that occurs once.
//
// Example
// Input: arr[] = {12, 1, 12, 3, 12, 1, 1, 1, 2, 3, 3};
// Output: 2
//
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>

// O(n) time complexity, and O(1) space complexity for bitwise solution
int get_single(std::vector<int> arr) {
  int ones = 0, twos = 0;
  int common_bit_mask;

  // { 3, 3, 2, 3 }
  for (int i = 0; i < arr.size(); ++i)
  {
    twos = twos | (ones & arr[i]);  // 
    ones = ones ^ arr[i];
    common_bit_mask = ~(ones & twos);
    ones &= common_bit_mask;
    twos &= common_bit_mask;
    std::cout << ones << ' ' << twos << std::endl;
  }

  return ones;
}

int main(int argc, char** argv)
{
  std::vector<int> a =  {12, 1, 12, 3, 12, 1, 1, 2, 3, 3};
  std::cout << "get single: " << get_single(a) << std::endl;

  // another solution
  // 3 * (sum_of_array_without_duplicates) - (sum_of_array) / 2

  return 0;
}
