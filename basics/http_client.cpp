#include "http_client.h"
#include <iostream>

std::string
HttpClient::SendHttpRequest(const std::string& url,
                            const std::string& data,
                            HttpMethod method)
{
  switch (method)
  {
  case HttpMethod::GET:
    std::cout << "Get method" << std::endl;
    break;

  case HttpMethod::PUT:
    std::cout << "Put method" << std::endl;
    break;

  case HttpMethod::POST:
    std::cout << "Post method" << std::endl;
    break;

  case HttpMethod::DELETE:
    std::cout << "Delete method" << std::endl;
    break;

  default:
    break;
  }
  return "Finish sending";
}
