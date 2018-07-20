#include <memory>
#include <fstream>
#include <ostream>
#include <exception>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>

namespace logging  = boost::log;
namespace attrs    = boost::log::attributes;
namespace src      = boost::log::sources;
namespace sinks    = boost::log::sinks;
namespace expr     = boost::log::expressions;
namespace keywords = boost::log::keywords;

enum {
  LOG_RECORDS_TO_WRITE = 10000,
  THREAD_COUNT = 2
};

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(test_lg, src::logger_mt)

// This function is executed in muitple threads
void thread_fun(boost::barrier& bar) {
  // Wait until all threads are created
  bar.wait();

  // now, do some logging
  for (unsigned int i = 0; i < LOG_RECORDS_TO_WRITE; ++i) {
    BOOST_LOG(test_lg::get()) << "Log record " << i;
  }
}

int main(int argc, char *argv[])
{
  try {
    // open a rotating text file
    boost::shared_ptr<std::ostream> strm(new std::ofstream("test.log"));
    if (!strm->good())
      throw std::runtime_error("Failed to open a text log file");

    // create a text file sink
    boost::shared_ptr<sinks::synchronous_sink<sinks::text_ostream_backend>> sink(
        new sinks::synchronous_sink<sinks::text_ostream_backend>);

    sink->locked_backend()->add_stream(strm);

    sink->set_formatter
    (
        expr::format("%1%: [%2%] [%3%] - [%4%]")
          % expr::attr<unsigned int>("RecordID")
          % expr::attr<boost::posix_time::ptime>("TimeStamp")
          % expr::attr<attrs::current_thread_id::value_type>("ThreadID")
          % expr::smessage
    );

    // add it to the core
    logging::core::get()->add_sink(sink);

    // Add some attributes too
    logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
    logging::core::get()->add_global_attribute("RecordID", attrs::counter<unsigned int>());
    logging::core::get()->add_global_attribute("ThreadID", attrs::current_thread_id());

    // create logging threads
    boost::barrier bar(THREAD_COUNT);
    boost::thread_group threads;

    for (unsigned int i = 0; i < THREAD_COUNT; ++i) {
      threads.create_thread(boost::bind(&thread_fun, boost::ref(bar)));
    }

    // wait until all action ends
    threads.join_all();

    return 0;
  } catch (std::exception &e) {
    std::cout << "FAILURE: " << e.what() << '\n';
    return 1;
  }
}
