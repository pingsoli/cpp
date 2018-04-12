///////////////////////////////////////////////////////////////////////////////
//
// Valid Parentheses
//
// Given a string containing just the characters '(', ')', '{', '}', '[', ']',
// determine if the input string is valid.
//
// the brackets must close in correct order, "()", and "()[]{}" are all valid
// but "(]" and "([)]" are not.
//
// Solution
// stack
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

///////////////////////////////////////////////////////////////////////////////
//
// standard solution

bool is_valid(const std::string& s)
{
  std::stack<char> stack;

  for (int i = 0; i < s.size(); ++i)
  {
    switch (s[i])
    {
    case '(':
    case '[':
    case '{': stack.push(s[i]); break;

    case ']':
      if (stack.empty() || stack.top() != '[') return false;
      else stack.pop(); break;
    case ')':
      if (stack.empty() || stack.top() != '(') return false;
      else stack.pop(); break;
    case '}':
      if (stack.empty() || stack.top() != '{') return false;
      else stack.pop(); break;

    default: ; // pass
    }
  }
  return stack.empty();
}

///////////////////////////////////////////////////////////////////////////////
//
// Use a map

//bool is_valid(const std::string& s)
//{
//  std::stack<char> stack;
//  std::unordered_map<char, char> m =
//    { { ']', '[' }, { ')', '(' }, { '}', '{' } };
//
//  for (int i = 0; i < s.size(); ++i)
//  {
//    if (s[i] == '[' || s[i] == '(' || s[i] == '{')
//      stack.push(s[i]);
//    else if (s[i] == ']' || s[i] == ')' || s[i] == '}')
//    {
//      if (stack.empty() || stack.top() != m[s[i]]) return false;
//      else stack.pop();
//    }
//  }
//
//  return stack.empty();
//}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Empty string
  {
    std::string s;
    std::cout << std::boolalpha << "empty string: " << is_valid(s) << '\n';
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // One parenthese
  {
    std::string s("()");
    std::cout << std::boolalpha << is_valid(s) << '\n';
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Embeded parentheses
  {
    std::string s("([{}()])");
    std::cout << std::boolalpha << is_valid(s) << '\n';
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Wrong
  {
    std::string s("([)]");
    std::cout << std::boolalpha << is_valid(s) << '\n';
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  //
  {
    std::string s("([])]()");
    std::cout << std::boolalpha << is_valid(s) << '\n';
  }

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
