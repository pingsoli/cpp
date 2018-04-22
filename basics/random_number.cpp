////////////////////////////////////////////////////////////////////////////////
//
// Generate random number
//
// Tree entities: Generator, engine and distribution.
//
// The problem of rand() function ?
// Pseudo random number, rand() will generate same number at the same time.
// It's not stable.
//
// What is seed ?
// Generating numbers imply executing algorithm, each new number depending one
// way or another on the last generator number(or a number or more from
// previous interation). That means any such algorithm needs an initial value,
// Called a "seed".
//
// How to choose a seed ?
// It's not a big deal, choose one you like.
//
// Concurrency
// std::random library provides thread-safe ways to produce random number.
// but rand() function can not.
//
// References
// [1] Marius Bancila. 2008. A TR1 Tutorial: Generating Random Numbers.
// https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c15319/A-TR1-Tutorial-Generating-Random-Numbers.htm
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <random>

std::uniform_int_distribution<uint32_t> uint_dist;  // range [0, UINT_MAX]
std::uniform_int_distribution<uint32_t> uint_dist10(0, 10);  // range [0, 10]

// std::normal_distribution<double> normal_dist(mean, stddeviation);

int main(int argc, char** argv)
{
  std::random_device rd;  // Used to botain a seed from the random number engine
  std::mt19937 gen(rd());  // generator

  for (int i = 0; i < 20; ++i)
    std::cout << uint_dist(gen) << " "
              << uint_dist10(gen) << std::endl;

  return 0;
}
