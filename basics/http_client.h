#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include <string>

class HttpClient
{
public:
  HttpClient() {}

  enum class HttpMethod { GET = 0, PUT, POST, DELETE };

  std::string SendHttpRequest(const std::string& url,
                              const std::string& data,
                              HttpMethod method);

private:
};

#endif /* __HTTP_CLIENT_H__ */
