////////////////////////////////////////////////////////////////////////////////
// specify your own allocator
//
// references
// [1] https://www.youtube.com/watch?v=pP15kDeXJU0
// [2] https://en.cppreference.com/w/cpp/named_req/Allocator
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <limits>
#include <iostream>

template <typename T>
class TrackingAllocator
{
public:
  using value_type = T;
  using size_type  = size_t;
  using pointer    = T *;

  TrackingAllocator()  = default;
  ~TrackingAllocator() = default;

  template <typename U>
  constexpr TrackingAllocator(const TrackingAllocator<U>& other) {}

  pointer allocate(size_type numOjbects) {
    mAllocations += numOjbects * sizeof(value_type);
    return static_cast<pointer>(operator new(sizeof(T) * numOjbects));
  }

  void deallocate(pointer p, size_type numOjbects) {
    operator delete(p);
  }

  size_type get_allocations() const {
    return mAllocations;
  }

private:
  static size_type mAllocations;
};

template <typename T>
typename TrackingAllocator<T>::size_type
TrackingAllocator<T>::mAllocations = 0;

int main(int argc, char *argv[])
{
  std::vector<int, TrackingAllocator<int>> vi(5);
  std::cout << "Assigned " << vi.get_allocator().get_allocations()
    << " bytes" << '\n';

  return 0;
}
