#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>

int32_t HexToInt(const std::string& hex)
{
  return std::stoi(hex, nullptr, 16);
}

#endif /* _UTILITY_H_ */
