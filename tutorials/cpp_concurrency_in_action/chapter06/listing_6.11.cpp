///////////////////////////////////////////////////////////////////////////////
//
// A thread-safe lookup table
//
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <boost/thread/shared_mutex.hpp>

///////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename Hash=std::hash<Key> >
class threadsafe_lookup_table
{
private:
  class bucket_type
  {
  private:
    typedef std::pair<Key, Value>          bucket_value;
    typedef std::list<bucket_value>        bucket_data;
    typedef typename bucket_data::iterator bucket_iterator;

    bucket_data                 data;
    mutable boost::shared_mutex mutex;

    bucket_iterator find_entry_for(Key const& key) const
    {
      return std::find_if(data.begin(), data.end(),
          [&](bucket_value const& item)
          { return item.first == key; });
    }

  public:
    Value value_for(Key const& key, Value const& default_value) const
    {
      boost::shared_lock<boost::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      return (found_entry == data.end()) ?
        default_value : found_entry->second;
    }

    void add_or_update_mapping(Key const& key, Value const& value)
    {
      std::unique_lock<boost::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      if (found_entry == data.end())
      {
        data.push_back(bucket_value(key, value));
      }
      else
      {
        found_entry->second = value;
      }
    }

    void remove_mapping(Key const& key)
    {
      std::unique_lock<boost::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      if (found_entry != data.end())
      {
        data.erase(found_entry);
      }
    }
  };

  std::vector<std::unique_ptr<bucket_type> > buckets;
  Hash hasher;

  bucket_type& get_bucket(Key const& key) const
  {
    std::size_t const bucket_index = hasher(key) % buckets.size();
    return *buckets[bucket_index];
  }

public:
  typedef Key   key_type;
  typedef Value value_type;
  typedef Hash  hash_type;

  threadsafe_lookup_table(
      unsigned num_buckets = 19, Hash const& hasher_ = Hash()) :
    buckets{num_buckets}, hasher{hasher_}
  {
    for (unsigned i = 0; i < num_buckets; ++i)
    {
      buckets[i].reset(new bucket_type);
    }
  }

  threadsafe_lookup_table(const threadsafe_lookup_table&) = delete;
  threadsafe_lookup_table& operator=(const threadsafe_lookup_table&) = delete;

  Value value_for(Key const& key,
      Value const& default_value = Value()) const
  {
    return get_bucket(key).value_for(key, default_value);
  }

  void add_or_update_mapping(Key const& key, Value const& value)
  {
    get_bucket(key).add_or_update_mapping(key, value);
  }

  void remove_mapping(Key const& key)
  {
    get_bucket(key).remove_mapping(key);
  }
};

///////////////////////////////////////////////////////////////////////////////

threadsafe_lookup_table<std::string, std::string> lookup_table;

// protect the cout
std::mutex cout_mutex;

///////////////////////////////////////////////////////////////////////////////
//
// multiple thread add or update data
// multiple thread erase from lookup table

// void produce()
// {
//   for (unsigned i = 0; i < 10; ++i)
//   {
//     lookup_table.add_or_update_mapping("pingsoli", "pingsoli@163.com");
//   }
// }
//
// void consume()
// {
//
// }

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  lookup_table.add_or_update_mapping("pingsoli", "pingsoli@163.com");
//  lookup_table.add_or_update_mapping("test", "test@qq.com");
//  std::cout << lookup_table.value_for("pingsoli") << std::endl;

  return 0;
}
