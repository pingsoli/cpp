///////////////////////////////////////////////////////////////////////////////
//
// Item 43: Know how to access names in templatized base classes
//
// Things to remember
//
// In derived class templates, refer to names in base class templates via
// a "this->" prefix, via using declarations, or via an explicit base class
// qualification.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class CompanyA {
public:
  void sendClearText(const std::string& msg) {
    std::cout << "CompanyA sendClearText " << msg << std::endl;
  }
  void sendEncrypted(const std::string& msg) {
    std::cout << "CompanyA sendEncrypted " << msg << std::endl;
  }
};

class CompanyB {
public:
  void sendClearText(const std::string& msg) {
    std::cout << "CompanyB sendClearText " << msg << std::endl;
  }
  void sendEncrypted(const std::string& msg) {
    std::cout << "CompanyB sendEncrypted " << msg << std::endl;
  }
};

template <typename Company>
class MsgSender {
public:
  void sendClear()
  {
    std::string msg;

    // do something, generate msg
    msg = "hello world";

    Company c;
    c.sendClearText(msg);
  }
};

template <typename Company>
class LoggerMsgSender : public MsgSender<Company>
{
public:

  void sendClearMsg()
  {
    std::cout << "before logging" << std::endl;

    sendClear(); // call base class function, this code will not compile!

    std::cout << "after logging" << std::endl;
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// three ways to do this:
//
// 1) this->sendClear();
//
// 2) using MsgSender<Company>::sendClear;
//
// 3) MsgSender<Company>::sendClear;
//
// the third way is the worst, but if the function is virtual, explicit
// qualification turns off the virtual binding behavior.
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  LoggerMsgSender<CompanyA> lsa;
  lsa.sendClearMsg();

  return 0;
}
