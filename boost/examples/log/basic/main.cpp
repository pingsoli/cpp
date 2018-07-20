#include <iostream>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

namespace logging  = boost::log;
namespace sinks    = boost::log::sinks;
namespace attrs    = boost::log::attributes;
namespace src      = boost::log::sources;
namespace expr     = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

// Here we define our application severity levels.
enum severity_level {
  normal,
  notification,
  warning,
  error,
  critical
};

// the formatting logic for the severity_level
template <typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& strm, severity_level lvl)
{
  static const char* const str[] = {
    "normal",
    "notification",
    "warning",
    "error",
    "critical"
  };

  if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
    strm << str[lvl];
  else
    strm << static_cast<int>(lvl);
  return strm;
}

int main(int argc, char *argv[])
{
  // The first thing we have to do to get using the library is to set up the
  // logging sinks
  logging::add_console_log(std::clog, keywords::format = "%TimeStamp%: %Message%");

  logging::add_file_log(
    "sample.log", // file stores log
    keywords::filter = expr::attr<severity_level>("Severity") >= warning,
    keywords::format = expr::stream
      << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f") << " "
      << "[" << expr::format_date_time<attrs::timer::value_type>("Uptime", "%O:%M:%S") << "] "
      << "[" << expr::format_named_scope("Scope", keywords::format = "%n (%f:%1)") << "] "
      << "<" << expr::attr<severity_level>("Severtiy") << "> "
      << expr::message
  );

  // also add some commonly used attributes, like timestamp and record counter
  logging::add_common_attributes();
  logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());

  // for name scope, function and line number
  BOOST_LOG_FUNCTION();

  src::logger lg;
  BOOST_LOG(lg) << "hello, world";

  // logging with severity defined by myself.
  src::severity_logger<severity_level> slg;
  slg.add_attribute("Uptime", attrs::timer());

  BOOST_LOG_SEV(slg, normal) << "A normal severity message, will not pass to the file";
  BOOST_LOG_SEV(slg, warning) << "A warning severity message, will pass to the file";
  BOOST_LOG_SEV(slg, error) << "An error severity message, will pass to the file";

  return 0;
}
