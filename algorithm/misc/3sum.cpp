////////////////////////////////////////////////////////////////////////////////
//
// 3 sum
// from https://leetcode.com/problems/3sum/description/
//
// Description
// given an array nums of n integers, are there elements a, b, c, in nums such
// that a + b + c = 0 ? Find all unique triples in the array which gives the
// sum of zero.
//
// NOTE:
// The solution set must not contain duplicate triplets
//
// Example
// Given array example = [-1, 0, 1, 2, -1, -4]
//
// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]
//
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <algorithm>

// I have no idea about the question.
// add two nums
std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
  std::vector<std::vector<int>> ret;

  std::sort(nums.begin(), nums.end());

  for (int i = 0; i < nums.size(); ++i) {

    int target = -nums[i];
    int front  = i + 1;
    int back   = nums.size() - 1;

    while (front < back) {

      int sum = nums[front] + nums[back];

      // Finding answer which start from number num[i]
      if (sum < target)
        front++;
      else if (sum > target)
        back--;
      else {
        std::vector<int> triplet(3, 0);
        triplet[0] = nums[i];
        triplet[1] = nums[front];
        triplet[2] = nums[back];
        ret.push_back(triplet);

        // Processing duplicate of Number 2
        // Rolling the front pointer to the next different number forwards
        while (front < back && nums[front] == triplet[1]) front++;

        // Processing duplicate of Number 3
        // Rolling the back pointer to the next different number backwards
        while (front < back && nums[back] == triplet[2]) back--;
      }
    }

    // Processing duplicates of number 1
    while (i + 1 < nums.size() && nums[i + 1] == nums[i])
      i++;
  }

  return ret;
}

int main(int argc, char** argv)
{
  std::vector<int> nums = {-1, 0, 1, 2, -1, -4};

  auto ret = three_sum(nums);

  for (int i = 0; i < ret.size(); ++i) {
    for (int j = 0; j < ret[i].size(); ++j)
      std::cout << ret[i][j] << ',';
    std::cout << std::endl;
  }

  return 0;
}
