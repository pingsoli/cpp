#include <thread>
#include <chrono>
#include <iostream>

class ThreadRAII {
public:
  enum class DtorAction { join, detach };

  // std::thread is not CopyConstructible or CopyAssignable, although it is
  // MoveConstructible and MoveAssignable.
  ThreadRAII(std::thread&& t, DtorAction a)
    : action(a), t(std::move(t)) {}

  ~ThreadRAII() {
    if (t.joinable()) {
      if (action == DtorAction::join) {
        t.join();
      } else {
        t.detach();
      }
    } // if it's not joinable, it detached already.
  }

  ThreadRAII(ThreadRAII&&) = default;             // support moving
  ThreadRAII& operator=(ThreadRAII&&) = default;

  std::thread& get() { return t; }

private:
  std::thread t;
  DtorAction action;
};

int main(int argc, char *argv[])
{
  {
    std::thread trd([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "thread" << '\n';
      });

    trd.detach();

    ThreadRAII t(std::move(trd), ThreadRAII::DtorAction::join);
  }

  return 0;
}
