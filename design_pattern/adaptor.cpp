// adaptor design pattern
// 1) make incompatible interfaces work together.
// 2) make class reusable when it does not have an interface that a client requires.
//
// Advantages
// It's very easy to implement, change, test and reuse.
//
// References
// https://www.youtube.com/watch?v=j9arNRRoPe8

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

// class String is a adaptor to fulfill our requirement.
class String {
public:
  String(const std::string& string_) :
    string(string_) {}

  String to_uppoer() const {
    std::string temp(string);
    std::transform(string.begin(), string.end(), temp.begin(),
        [] (unsigned char c) { return std::toupper(c); });
    return {temp};
  }

  String to_lower() const {
    std::string temp(string);
    std::transform(string.begin(), string.end(), temp.begin(),
        [] (unsigned char c) { return std::tolower(c); });
    return {temp};
  }

  std::vector<std::string> split(unsigned char delimiter) {
    std::vector<std::string> words;
    auto it = string.begin();

    while (it != string.end()) {
      while (it != string.end() && *it == delimiter) it++;

      auto next = std::find(it, string.end(), delimiter);
      words.emplace_back(it, next);

      it = next;
      while (it != string.end() && *it == delimiter) it++;
    }

    return words;
  }

  std::string str() const {
    return string;
  }

private:
  std::string string;
};

int main(int argc, char *argv[])
{
  String s("    heLlo     woRld   ");

  std::cout << s.to_lower().str() << '\n';
  auto words = s.split(' ');

  for (auto& word : words)
    std::cout << word.length() << " " << word << '\n';

  std::cout << s.to_uppoer().str() << '\n';

  return 0;
}
