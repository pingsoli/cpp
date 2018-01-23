#ifndef __TEXT_BLOCK_H__
#define __TEXT_BLOCK_H__

#include <string>
#include <string.h>

class TextBlock
{
public:
  TextBlock(const std::string& s)
    : text{s}
  {
  }

  const char& operator[](std::size_t position) const
  {
    std::cout << "const char& operator[]()\n";
    return text[position];
  }

//  char& operator[](std::size_t position)
//  {
//    std::cout << "char& operator[]()\n";
//    return text[position];
//  }

  char& operator[](std::size_t position)  // cast away const on
  {
    std::cout << "Call char& operator"
                 "[](std::size_t position"
                 << std::endl;                            // cast away const on
    return const_cast<char &>(                            // op[]'s return type
        static_cast<const TextBlock&>(*this)[position]);  // add const to *this's type
  }                                                       // call const version of op[]

  void print()
  {
    std::cout << text << std::endl;
  }

private:
  std::string text;
};

class CTextBlock
{
public:
  CTextBlock(const char *str)
  {
    pText = new char(1024);
    strncpy(pText, str, 1024);
  }

  std::size_t lenght() const
  {
    if (!lengthIsValid)
    {
      textLength = strlen(pText);
      lengthIsValid = true;
    }

    return textLength;
  }

  char& operator[](std::size_t position) const
  {
    return pText[position];
  }

  void print()
  {
    std::cout << pText << std::endl;
  }

private:
  char *pText;
  mutable std::size_t textLength;
  mutable bool lengthIsValid;
};

#endif /* __TEXT_BLOCK_H__ */
