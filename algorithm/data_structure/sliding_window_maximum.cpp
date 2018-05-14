////////////////////////////////////////////////////////////////////////////////
//
// Sliding Window Maximum
// https://leetcode.com/problems/sliding-window-maximum/description/
//
// Description
// Given an array nums, there is a sliding window of size k which is moving
// from the very left of the array to the very right. You can only see the k
// numbers in the window. Each time the sliding window moves right by one
// position. Return the max sliding window.
//
// Example:
//
// Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
// Output: [3,3,5,5,6,7]
// Explanation:
//
// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
//
// Note:
// You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.
//
// Follow up:
// Could you solve it in linear time?
//
////////////////////////////////////////////////////////////////////////////////

// dequue

#include <vector>
#include <iostream>
#include <deque>

std::vector<int> max_sliding_window(std::vector<int>& nums, int k)
{
  std::deque<int> dq;
  std::vector<int> ret;

  for (int i = 0; i < nums.size(); ++i) {
    if (!dq.empty() && dq.front() == i - k) dq.pop_front();
    while (!dq.empty() && nums[dq.back()] < nums[i])
      dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1) ret.push_back(nums[dq.front()]);
  }

  return ret;
}

int main(int argc, char** argv)
{
  std::vector<int> vi = {1, 3, -1, -3, 5, 3, 6, 7};
  std::vector<int> ret;
  int k = 3;

  ret = max_sliding_window(vi, k);

  for (int i = 0; i < ret.size(); ++i) {
    std::cout << ret[i] << ' ';
  }

  return 0;
}
