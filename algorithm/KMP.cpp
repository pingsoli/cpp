///////////////////////////////////////////////////////////////////////////////
//
// KMP Substring search
//
// Time Complexity
// average: O(n + m)
// worst:   O(m * n)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG 1

int kmp_search(const std::string& needle, const std::string& haystack)
{
  std::vector<int> border(needle.size(), 0);

  // process pattern string, construct the border table
  for (int i = 1, k = 0; i < needle.size(); ++i)
  {
    while (k && needle[k] != needle[i])
      k = border[k - 1];

    if (needle[k] == needle[i])
      ++k;

    border[i] = k;
  }

  /////////////////////////////////////////////////////////////////////////////

#if DEBUG
  std::for_each(border.begin(), border.end(),
      [&](const int& item) {
        std::cout << item << ' ';
      });
  std::cout << std::endl;
#endif

  /////////////////////////////////////////////////////////////////////////////

  for (int i = 0, k = 0; i < haystack.size(); ++i)
  {
    while (k && needle[k] != haystack[i])
      k = border[k - 1];

    if (needle[k] == haystack[i]) ++k;
    if (k == needle.size()) return i - k + 1;
  }

  return -1;
}

int main(int argc, char** argv)
{
  std::string haystack("test");
  std::string needle("aabaabaaaab");
  int index{-1};


  do {
    index = kmp_search(needle, haystack);

    if (index > 0)
      std::cout << "Found, index: " << index << '\n';
    else
      std::cout << "Not found\n";

    std::cout << "please enter haystack: ";
    getline(std::cin, haystack);

    std::cout << "please enter needle: ";
    getline(std::cin, needle);
  } while (true);

  return 0;
}
