///////////////////////////////////////////////////////////////////////////////
// std::async and std::future testing
//
// Don't care about the processing of the data, get the data at the end.
// Maybe It will spend much time, but I don't care.
//
// std::async default behavior won't create a new thread.
// We must specify std::launch::async on the std::async.
//
// std::deferred, std::async
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <numeric>

// protect std::cout
std::mutex cout_mutex;

int do_async_job() {
  std::lock_guard<std::mutex> lk(cout_mutex);
  std::cout << "async thread id: " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return 100;
}

void do_other_thing() {
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

double Foo(double d) {
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
  return d * 5.0;
}

int main(int argc, char** argv)
{
  {
    // auto start = std::chrono::high_resolution_clock::now();
    //
    // // Don't add std::launch::async, async job will run on the same thread, or
    // // async will create a new thread and run on the background.
    // //
    // // future.get() will make main thread wait for the async thread.
    //
    // std::future<int> the_answer = std::async(std::launch::async, do_async_job);
    // do_other_thing();
    //
    // std::lock_guard<std::mutex> lk(cout_mutex);
    // std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
    // std::cout << "the last answer is: " << the_answer.get() << std::endl;
    //
    // // Async thread sleep 2s, main thread sleep 2s, but the answer it not 4s.
    // // It's 2s, but is not precise.
    //
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> elapsed = end - start;
    // std::cout << "programming executing: " << elapsed.count()
    //   << " ms" << std::endl;
  }

  {
    std::vector<double> values{1.0, 2.0, 3.0, 4.0};
    std::vector<std::future<double>> answers;
    double total = 0.0;

    for (double value : values)
      answers.push_back(std::async(std::launch::async, Foo, value));

    // total = std::accumulate(begin(answers), end(answers), 0.0,
    //     [] (double x, std::future<double>& t) { return x + t.get(); });

    for (auto &a : answers)
      total += a.get();

    std::cout << "Total num: " << total << '\n';
  }

  return 0;
}
