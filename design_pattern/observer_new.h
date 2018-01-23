#ifndef _OBSERVER_NEW_H_
#define _OBSERVER_NEW_H_

#include <functional>
#include <map>
#include <vector>
#include <utility>

template <typename Event>
class Subject
{
public:
  Subject() = default;

  template <typename Observer>
  void registerObserver(const Event& event, Observer&& observer)
  {
    observers_[event].push_back(std::forward<Observer>(observer));
  }

  template <typename Observer>
  void registerObserver(Event&& event, Observer&& observer)
  {
    observers_[std::move(event)].push_back(std::forward<Observer>(observer));
  }

  void notify(const Event& event) const
  {
    for (const auto& obs : observers_.at(event)) obs();
  }

  // Disallow copying and assigning
  Subject(const Subject&) = delete;
  Subject& operator=(const Subject&) = delete;

private:
  std::map<Event, std::vector<std::function<void ()>>> observers_;
};

#endif /* _OBSERVER_NEW_H_ */
