///////////////////////////////////////////////////////////////////////////////
//
// Two Sum
//
// Reference
// https://leetcode.com/problems/two-sum/solution/
//
///////////////////////////////////////////////////////////////////////////////
//
// Description
// Given an array of integers, return indices of the two numbers such that
// add up to a specific target.
// you may assume that each input would have exactly one solution, and you
// may not use the same element twice.
//
///////////////////////////////////////////////////////////////////////////////
//
// Example
// Given nums = [2, 7, 11, 15]
// Because nums[0] + nums[1] = 9
// return [0, 1]
//
///////////////////////////////////////////////////////////////////////////////
//
// Solution
// 1) Brute Force
// 2) Two-pass Hash Table
// 3) One-pass Hash Table
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
//
// One-pass Hash Table
// Time complexity: O(n), each lookup in the table costs only O(1) time.
// Space complexity: O(n)

std::pair<int, int> two_sum(std::vector<int> nums, int target)
{
  std::unordered_map<int, int> map;

  for (int i = 0; i < nums.size(); ++i)
  {
    int complement = target - nums[i];
    if (map.find(complement) != map.end())
    {
      // for test
//      for (auto it = map.cbegin(); it != map.cend(); ++it)
//      {
//        std::cout << it->first << ' ' << it->second << '\n';
//      }

      return std::make_pair(map[complement], i);
    }
    map.emplace(nums[i], i);
  }
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  std::vector<int> vi{2, 4, 4, 6, 7, 11, 13, 15, 20};
  int target = 9;

  std::cout << "Array: [";
  std::for_each(vi.begin(), vi.end(), [&](const int e) {
      std::cout << e << ',';
      });
  std::cout << "]\n";

  std::cout << "Please enter your target: ";
  std::cin >> target;

  auto result = two_sum(vi, target);

  std::cout << '[' << result.first << ',' << result.second << ']' << std::endl;

  return 0;
}
