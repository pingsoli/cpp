///////////////////////////////////////////////////////////////////////////////
//
// Description
// Given a digit string, return all possible letter combinations that the
// number could represent.
//
// Reference
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
// https://github.com/zhuli19901106/leetcode-2
//
// Solution
// It looks like DFS(depth first search), use recursion will solve it.
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> phone_letters;

void dfs(std::string& s, const std::string& digits,
                         std::vector<std::string>& res)
{
  int idx = s.size();
  if (idx == digits.size())
  {
    res.push_back(s);
    return;
  }

  int d = digits[idx] - '0';
  for (int i = 0; i < phone_letters[d].size(); ++i)
  {
    s.push_back(phone_letters[d][i]);
    dfs(s, digits, res);
    s.pop_back(); // why need this? every push operation need pop to previous
                  // level
  }
}

std::vector<std::string> letter_combinations(const std::string& digits)
{
  std::vector<std::string> res;
  if (digits.size() == 0)
  {
    return res;
  }

  std::string s = "";
  dfs(s, digits, res);
  return res;
}

int main(int argc, char** argv)
{
  // store phone number(just like phone buttons)
  phone_letters.push_back("");
  phone_letters.push_back("");
  phone_letters.push_back("abc");  // map to '2' button
  phone_letters.push_back("def");  // map to '3' button
  phone_letters.push_back("ghi");  // map to '4' button
  phone_letters.push_back("jkl");  // map to '5' button
  phone_letters.push_back("mno");  // map to '6' button
  phone_letters.push_back("pqrs"); // map to '7' button
  phone_letters.push_back("tuv");  // map to '8' button
  phone_letters.push_back("wxyz"); // map to '9' button

  std::vector<std::string> res;
  std::string input_digits_str;

  std::cout << "Please enter digits number: ";
  std::cin >> input_digits_str;

  res = letter_combinations(input_digits_str);

  // traverse the result
  std::for_each(res.begin(), res.end(),
      [](const std::string& s) {
        std::cout << s << ' ';
      });
  std::cout << std::endl;  // flush std::cout avoiding

  return 0;
}
