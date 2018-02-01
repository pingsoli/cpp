#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

#include <boost/coroutine2/all.hpp>

// ####################################################################
// coroutine<>::push_type provides output iterators(
// coroutine<>::push_type::iterator) and std::begin() and std::end() are
// overloaded. The increment-operation swithches the context and transfer
// data.

typedef boost::coroutines2::coroutine<std::string> coro_t;

struct FinalEOL {
  ~FinalEOL() {
    std::cout << std::endl;
  }
};

// make clear of the execution flow?
// 1) first run push_type scope
// 2) push_type scope invoke pull_type(sink)
// 3) pull_type do something
// 4) pull_type scope call push_type(source)
// 5) ....
// 6) at last, give back to push_type
// 7) end
//
void simple_example()
{
  const int num = 5, width = 15;
  coro_t::push_type writer(
    [&](coro_t::pull_type& in) {
    // finish the last line when we leave by whatever means
    FinalEOL eol;
    // pull values from upstream, lay them out 'num' to a line.
    for (;;) {
      for (int i = 0; i < num; ++i) {
        // when we exhaust the input, stop
        if (!in) return;
        std::cout << std::setw(width) << in.get();
        // now that we've handle this item, advance to next
        in();
      }
      // after 'num' items, like break
      std::cout << std::endl;
    }
  });

  std::vector<std::string> words{
    "peas", "porridge", "hot", "peas",
    "porridge", "cold", "peas", "porridge",
    "in", "the", "pot", "nine",
    "days", "old"
  };

  // Copy what? copy to where? how to receive?
  // regard coroutine as a iterable object.
  // overload std::begin() and std::end()
  // when to call writer()?
  std::copy(begin(words), end(words), begin(writer));
}

// deliver each line of input stream to sink as a separate string
void readlines(coro_t::push_type& sink, std::istream& in) {
  std::string line;
  while (std::getline(in, line))
    sink(line);
}

void tokenize(coro_t::push_type& sink, coro_t::pull_type& source) {
  // This is tokenizer doesn't happen to be stateful: you could
  // resonably implement it with a single call to push each new
  // token downstream. But I've worked with stateful tokenizers, in
  // which meaning of input characters depends in part on their position
  // within the input line.
  for (std::string line : source) {
    std::string::size_type pos = 0;
    while (pos < line.length()) {
      if (line[pos] == '"') {
        std::string token;
        ++pos;       // skip open quote
        while (pos < line.length() && line[pos] != '"')
          token += line[pos++];
        ++pos;       // skip close quote
        sink(token); // pass token downstream
      } else if (std::isspace(line[pos])) {
        ++pos;       // outside quotes, ignore whitespace
      } else if (std::isalpha(line[pos])) {
        std::string token;
        while (pos < line.length() && std::isalpha(line[pos]))
          token += line[pos++];
        sink(token);  // pass token downstream
      } else {        // punctuation
        sink(std::string(1, line[pos++]));
      }
    }
  }
}

// remove punctuation
void only_words(coro_t::push_type& sink, coro_t::pull_type& source) {
  for (std::string token : source) {
    if (!token.empty() && std::isalpha(token[0]))
      sink(token);
  }
}

void trace(coro_t::push_type& sink, coro_t::pull_type& source) {
  for (std::string token : source) {
    std::cout << "trace: '" << token << "'\n";
    sink(token);
  }
}

void layout(coro_t::pull_type& source, int num, int width) {
  // Finish the last line when we leave by whatever means
  FinalEOL eol;

  // Pull values from upstream, lay them out 'num' to a line
  for (;;) {
    for (int i = 0; i < num; ++i) {
      // when we exhaust the input, stop
      if (!source) return;

      std::cout << std::setw(width) << source.get();
      // now that we've handle this item, advance to next
      source();
    }

    // after 'num' items, line break
    std::cout << std::endl;
  }
}

int main()
{
  std::string data(
    "This is the first line.\n"
    "This, the second.\n"
    "The third has \"a phrase\"!\n"
  );

  using namespace std::placeholders;

  std::cout << "Original string: \n" << data << '\n';

  {
    std::cout << "\nfilter:\n";
    std::istringstream infile(data);
    coro_t::pull_type reader(std::bind(readlines, _1, std::ref(infile)));
    coro_t::pull_type tokenizer(std::bind(tokenize, _1, std::ref(reader)));
    coro_t::pull_type filter(std::bind(only_words, _1, std::ref(tokenizer)));
    coro_t::pull_type tracer(std::bind(trace, _1, std::ref(filter)));

    for (std::string token : tracer) {
      // just iterate, we're already pulling through tracer
    }
  }

  {
    std::cout << "\nlayout() as coroutine::push_type:\n";
    std::istringstream infile(data);
    coro_t::pull_type reader(std::bind(readlines, _1, std::ref(infile)));
    coro_t::pull_type tokenizer(std::bind(tokenize, _1, std::ref(reader)));
    coro_t::pull_type filter(std::bind(only_words, _1, std::ref(tokenizer)));
    coro_t::push_type writer(std::bind(layout, _1, 5, 15));

    for (std::string token : filter) {
      writer(token);
    }
  }

  {
    std::cout << "\nfiltering output:\n";
    std::istringstream infile(data);
    coro_t::pull_type reader(std::bind(readlines, _1, std::ref(infile)));
    coro_t::pull_type tokenizer(std::bind(tokenize, _1, std::ref(reader)));
    coro_t::push_type writer(std::bind(layout, _1, 5, 15));
    coro_t::push_type filter(std::bind(only_words, std::ref(writer), _1));

    for (std::string token : tokenizer) {
      filter(token);
    }
  }

  return 0;
}

// output:
//           peas       porridge            hot           peas       porridge
//           cold           peas       porridge             in            the
//            pot           nine           days            old
