////////////////////////////////////////////////////////////////////////////////
// 手里有一副 1 到 n 的牌，每次从牌堆顶取一张放在桌子上，再取一张放牌堆底，
// 直到手里没有牌。现在，桌子上的牌是 1 到 n 有序的。设计程序，输入 n，输入牌堆
// 的顺序数组。
////////////////////////////////////////////////////////////////////////////////
// cards sequence: [1 5 2 4 3]
// pick out the top card to another container,
// and then pick out the top card to put it to the bottom. This is one step.
//
// [1 5 2 4 3]
// [1] [2 4 3 5] // step 1
// [1 2] [3 5 4] // step 2
// [1 2 3] [4 5] // step 3, we got the answer, but it's not so much clear.
// [1 2 3 4] [5] // step 4
// [1 2 3 4 5]   // step 5, we got the sequence from 1 to 5.
//
//
// cards sequence: [1 2 3 4 5]
// [1] [3 4 5 2] // step 1
// [1 3] [5 2 4] // step 2
// [1 3 5] [4 2] // step 3, right is three, left is two. the answer is clear.
// [1 3 5 4] [2] // step 4
// [1 3 5 4 2]   // step 5, we got the result from [1 2 3 4 5].
//
//
// and then we analysis the relationship between them, we can found that.
// [1, 5, 2, 4, 3] origin  (that's what we want)
// [1, 3, 5, 4, 2] mapping (index of origin)
// [1, 2, 3, 4, 5] final   (data of origin)
//
// computation formula: NOTE: index starts from 1.
// origin[mapping[1]] = final[1]
// origin[mapping[2]] = final[2]
// origin[mapping[3]] = final[3]
// origin[mapping[4]] = fianl[4]
// origin[mapping[5]] = fianl[5]
//
// more conciser:
// origin[mapping[0]] = 1;
// origin[mapping[1]] = 2;
// origin[mapping[2]] = 3;
// origin[mapping[3]] = 4;
// origin[mapping[4]] = 5;

#include <vector>
#include <iostream>
#include <exception>

std::vector<int> final;
std::vector<int> mapping;
std::vector<int> origin;

void playcards() {
  while (!final.empty()) {
    // first, pick out the top card and put it to another container.
    mapping.push_back(*final.begin());
    final.erase(final.begin());

    if (final.empty()) break;

    // second, pick out the top card and put it to bottom.
    final.push_back(*final.begin());
    final.erase(final.begin());
  }

  for (int i = 0; i < mapping.size(); ++i)
    origin[mapping[i] - 1] = i + 1;
}

void traverse(std::vector<int>& vi)
{
  for (auto it = vi.begin(); it != vi.end(); ++it)
    std::cout << *it << ' ';
  std::cout << '\n';
}

int main(int argc, char *argv[])
{
  int n = 0;

  try {
    while (true) {
      std::cout << "Please enter number n: ";
      std::cin >> n;

      if (0 == n) break;

      final.resize(n);
      origin.resize(n);

      for (int i = 0; i < n; ++i) final[i] = i + 1;

      traverse(final);
      playcards();
      traverse(origin);

      mapping.clear(); // empty the mapping vector, and the size change to 0.
    }
  } catch (std::exception& e) {
    std::cout << e.what() << '\n';
  } catch (...) {
    std::cout << "Unknown exception" << '\n';
  }

  return 0;
}
