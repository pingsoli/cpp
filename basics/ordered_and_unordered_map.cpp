///////////////////////////////////////////////////////////////////////////////
//
// PERFORMANCE
// unordered_map Vs. map (ordered)
// +----------------+---------------------+--------------------+
// | Ordering       | Increasing order    | no ordering        |
// |                | (by deafult)        |                    |
// +----------------+---------------------+--------------------+
// | Implementation | Self balancing BST  | Hash Table         |
// |                | like Red-Black Tree |                    |
// +----------------+---------------------+--------------------+
// | Search time    | log(n)              | O(1) -> Average    |
// |                |                     | O(1) -> Worst case |
// +----------------+---------------------+--------------------+
// | Insertion time | log(n) + Rebalance  | same as search     |
// +----------------+---------------------+--------------------+
// | Deletion time  | log(n) + Rebalance  | same as search     |
// +----------------+---------------------+--------------------+
//
// References
// [1] https://www.geeksforgeeks.org/map-vs-unordered_map-c/
// [2] https://github.com/greg7mdp/sparsepp
//
// SUMMARY:
// so, if we don't care about the key order, we can use unordered map.
// In common case, we recommand unordered_map.
//
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <unordered_map>
#include <iostream>
#include "util.hpp"

std::map<int, int>           om;
std::unordered_map<int, int> um;

int main(int argc, char** argv)
{
  return 0;
}
