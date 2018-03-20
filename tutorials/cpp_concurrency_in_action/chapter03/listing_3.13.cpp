///////////////////////////////////////////////////////////////////////////////
//
// exclusive access by a single "writer" thread or shared, concurrent accesss
// by multiple "reader" threads.
//
// c++ standards don't provide that mutex, but boost library support it.
// boost::shared_mutex
//
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include <mutex>
#include <boost/thread/shared_mutex.hpp>

class dns_entry
{};

class dns_cache
{
private:
  std::map<std::string, dns_entry> entries;
  boost::shared_mutex entry_mutex;

public:
  dns_entry find_entry(const std::string& domain)
  {
    boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
    std::map<std::string, dns_entry>::const_iterator const it =
      entries.find(domain);
    return (it == entries.end()) ? dns_entry() : it->second;
  }

  void update_or_add_entry(const std::string& domain,
      const dns_entry& dns_details)
  {
    std::lock_guard<boost::shared_mutex> lk(entry_mutex);
    entries[domain] = dns_details;
  }
};

int main(int argc, char** argv)
{
  return 0;
}
