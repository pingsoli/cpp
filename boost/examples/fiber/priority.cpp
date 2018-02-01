#include <chrono>
#include <condition_variable>
#include <mutex>
#include <algorithm>

#include <boost/fiber/all.hpp>
#include <boost/fiber/scheduler.hpp>

class Verbose {
public:
  Verbose(std::string const& d, std::string const& s = "stop") :
    desc(d),
    stop(s)
  {
    std::cout << desc << " start" << std::endl;
  }

  ~Verbose()
  {
    std::cout << desc << ' ' << stop << std::endl;
  }

  Verbose(Verbose const&)              = delete;
  Verbose & operator=(Verbose const &) = delete;

private:
  std::string desc;
  std::string stop;
};

class priority_props : public boost::fibers::fiber_properties {
public:
  priority_props(boost::fibers::context * ctx) :
    fiber_properties(ctx),
    priority_{0}
  {}

  int get_priority() const {
    return priority_;
  }

  void set_prioriry(int p) {
    if (p != priority_) {
      priority_ = p;
      notify();
    }
  }

  std::string name;

private:
  int priority_;
};

class priority_scheduler :
  public boost::fibers::algo::algorithm_with_properties<priority_props> {
private:
  typedef boost::fibers::scheduler::ready_queue_type rqueue_t;

  rqueue_t                rqueue_;
  std::mutex              mtx_{};
  std::condition_variable cnd_{};
  bool                    flag_{ false };

public:
  priority_scheduler() :
    rqueue_()
  {}
};
