///////////////////////////////////////////////////////////////////////////////
//
// String Algorithms
// searching: double-for, KMP
//
// FAQ:
// 1. string.find() use what kind of algorithm ? KMP
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

// Double-for-loop is the easiest approach to implement string searching
int strStr(std::string haystack, std::string needle)
{
  if (haystack.empty() && needle.empty()) return 0;
  if (haystack.empty()) return -1;
  if (haystack.size() < needle.size()) return -1;

  for (int i = 0; i < haystack.size() - needle.size() + 1; ++i)
  {
    int j = 0;
    for (; j < needle.size(); ++j)
    {
      if (haystack[i + j] != needle[j]) break;
    }

    if (j == needle.size()) return i;
  }

  return -1;
}

int main(int argc, char** argv)
{
  std::string s("hello world wtf ehladj/dafj");
  std::string sub_str("wtf");

  std::cout << "Searching string: " << s << std::endl;
  std::cout << "searchinf for: " << sub_str << std::endl;

  int found = strStr(s, sub_str);
  if (found < 0)
    std::cout << "\"" << sub_str << "\" NOT Found\n";
  else
    std::cout << "\"" << sub_str << "\" locate in " << found << std::endl;

  // the same answer as the above code
  std::cout << s.find(sub_str) << std::endl;

  return 0;
}
