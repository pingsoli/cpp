#include <iostream>
#include <string>

#include <boost/thread/thread.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_multifile_backend.hpp>

namespace logging  = boost::log;
namespace attrs    = boost::log::attributes;
namespace src      = boost::log::sources;
namespace sinks    = boost::log::sinks;
namespace expr     = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

enum {
  THREAD_COUNT = 5,
  LOG_RECORD_TO_WRITE = 10
};

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt);

void thread_foo() {
  BOOST_LOG_SCOPED_THREAD_TAG("ThreadID", boost::this_thread::get_id());
  for (unsigned int i = 0; i < LOG_RECORD_TO_WRITE; ++i) {
    BOOST_LOG(my_logger::get()) << "Log record " << i;
  }
}

int main(int argc, char *argv[])
{
  typedef sinks::synchronous_sink<sinks::text_multifile_backend> file_sink_t;
  shared_ptr<file_sink_t> sink(new file_sink_t);

  sink->locked_backend()->set_file_name_composer(
      sinks::file::as_file_name_composer(
        expr::stream << "logs/" << expr::attr<boost::thread::id>("ThreadID")
        << ".log"));

  sink->set_formatter
  (
    expr::format("%1%: [%2%] - %3%")
      % expr::attr<unsigned int>("RecordID")
      % expr::attr<boost::posix_time::ptime>("TimeStamp")
      % expr::smessage
  );

  logging::core::get()->add_sink(sink);

  logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
  logging::core::get()->add_global_attribute("RecordID", attrs::counter<unsigned int>());

  boost::thread_group threads;

  for (unsigned int i = 0; i < THREAD_COUNT; ++i)
    threads.create_thread(&thread_foo);

  threads.join_all();

  return 0;
}
