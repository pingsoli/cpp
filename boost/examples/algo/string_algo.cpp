/*
 * Overview
 *   Case conversion
 *   Predication and classification
 *   Trimming
 *   Find algorithms
 *   Replace algorithms
 *   Find iterator
 *   Split
 *
 * Summary
 *   Predicate is our good friend, it describes a callable that returns a value
 *   testable as a bool (main point).
 *   details: http://en.cppreference.com/w/cpp/concept/Predicate
 */
#include <iostream>
#include <functional>  // bind2nd
#include <algorithm>   // plus

#include <boost/algorithm/string/case_conv.hpp>       // to_upper
#include <boost/algorithm/string/predicate.hpp>       // all
#include <boost/algorithm/string/classification.hpp>  // is_lower, is_any_of
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/find_format.hpp>

#include <boost/algorithm/string/finder.hpp>   // first_finder
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/compare.hpp>  // is_euqal

#include <boost/algorithm/string/split.hpp>    // ifind_all

using namespace std;
using namespace boost::algorithm;

bool is_executable(string const& filename)
{
  return
    iends_with(filename, ".exe") ||
    iends_with(filename, ".com");
}

int main(int argc, char** argv)
{

  std::string case_str("HellO WoRld");

  /**********************************************************************
   * Case conversion
   *
   * Mutable:
   *   1) to_upper()
   *   2) to_lower()
   *
   * Copy:
   *   1) to_upper_copy()
   *   2) to_lower_copy()
   *
   *********************************************************************/
  to_upper(case_str);
  std::cout << to_upper_copy(case_str) << '\n';

  to_lower(case_str);
  std::cout << to_lower_copy(case_str) << '\n';

  /*********************************************************************
   * Predication and classfication
   ********************************************************************/
  std::string predic_name("command.com");
  std::cout << predic_name
            << (is_executable(predic_name) ? " is" : " is not")
            << " an executable"
            << std::endl;

  char text1[] = "hello";
  std::cout << text1
            << (all(text1, is_lower()) ? " is" : " is not")
            << " written in the lower case"
            << std::endl;

  /*********************************************************************
   * Trimming
   ********************************************************************/
  std::string str1 = "    hello world !    ";
  std::string str2 = trim_left_copy(str1);  // str2 == "hello world !    ";
  std::string str3 = trim_right_copy(str1); // str3 == "    hello world !";
  trim(str1);  // str1 == "hello world !";

  std::cout << str2 << '\n'
            << str3 << '\n'
            << str1 << std::endl;

  /*********************************************************************
   * Find algorithm
   ********************************************************************/
  char text[] = "hello dolly!";
  boost::iterator_range<char*> result = find_last(text, "ll");

  transform(result.begin(), result.end(),
    result.begin(), std::bind2nd(plus<char>(), 1));

  std::cout << text << std::endl;  // text == "hello dommy!"

  /*********************************************************************
   * Replace algorithm
   ********************************************************************/
  string hello = "hello dolly, hello world";
  replace_first(hello, "dolly", "pingsoli"); // hello pingsoli, hello world
  replace_first(hello, "hello", "Goodbye");  // Goodbye pingsoli, hello world

  erase_all(hello, " ");  // Goodbyepingsoli,helloworld
  erase_head(hello, 6);   // epingsoli,helloworld

  /*********************************************************************
   *
   * Find algorithm
   *
   * find_iterator and split_iterator
   *
   ********************************************************************/
  std::string find_str("abc-*-ABC-*-aBc");
  // Find all 'abc' substring (ignoring the case)
  // Create find_iterator
  typedef find_iterator<std::string::iterator> string_find_iterator;

  for (string_find_iterator it =
      boost::make_find_iterator(find_str, first_finder("abc", is_iequal()));
    it != string_find_iterator();
    ++it
  )
  {
    std::cout << boost::copy_range<std::string>(*it) << std::endl;
  }

  // output:
  // abc
  // ABC
  // aBc

  typedef split_iterator<std::string::iterator> string_split_iterator;

  for (string_split_iterator it =
      boost::make_split_iterator(find_str, first_finder("-*-", is_equal()));
    it != string_split_iterator();
    ++it
  )
  {
    std::cout << boost::copy_range<std::string>(*it) << std::endl;
  }

  // output:
  // abc
  // ABC
  // aBc

  /*********************************************************************
   * Split algorithm
   ********************************************************************/
  std::string split_str("hello abc-*-ABC-*-aBc goodbye");

  typedef std::vector<
            boost::iterator_range<std::string::iterator>
                     > find_vector_type;

  find_vector_type FindVec;
  ifind_all(FindVec, split_str, "abc");

  for (auto it : FindVec) {
    std::cout << it << std::endl;
  }

  // output:
  // abc
  // ABC
  // aBc

  typedef std::vector<std::string> split_vector_type;
  split_vector_type SplitVec;

  split(SplitVec, split_str, is_any_of("-*-"), token_compress_on);

  for (auto it : SplitVec) {
    std::cout << it << std::endl;
  }

  // output:
  // hello abc
  // ABC
  // aBc goodbye

  return 0;
}
