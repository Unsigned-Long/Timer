#include <algorithm>
#include <random>
#include <vector>

#include "timer.h"

using namespace ns_timer;

void foo_timer() {
  // define a timer
  Timer timer;
  // do something : generate elems and push_back to vec
  std::vector<int> vec;
  for (int i = 0; i != 100000; ++i)
    vec.push_back(i);
  // output the period of the last duration
  std::cout << timer.last_elapsed<DurationType::MS>("create vector")
            << std::endl;
  // do something : shuffle
  std::shuffle(vec.begin(), vec.end(), std::default_random_engine());
  // output the period of the last duration
  std::cout << timer.last_elapsed("shuffle vector") << std::endl;
  // do something : sort
  std::sort(vec.begin(), vec.end());
  // output the period of the last duration
  std::cout << timer.last_elapsed("sort vector") << std::endl;
  // output the period of the total duration
  std::cout << timer.total_elapsed("total cost") << std::endl;
  // sleep for 2s
  timer.re_start();
  ns_timer::sleep<DurationType::S>(2);
  std::cout << timer.last_elapsed<DurationType::MS>("sleep") << std::endl;
  return;
}

void foo_timer_monitor() {

  // define a timer
  TimerMonitor monitor;
  // do something : generate elems and push_back to vec
  monitor.sow("total cost");
  monitor.sow("create a vector");
  std::vector<int> vec;
  for (int i = 0; i != 100000; ++i)
    vec.push_back(i);
  // output the period of the last duration
  std::cout << monitor.reap("create a vector")
            << std::endl;
  // do something : shuffle
  monitor.sow("shuffle vector");
  std::shuffle(vec.begin(), vec.end(), std::default_random_engine());
  // output the period of the last duration
  std::cout << monitor.reap("shuffle vector") << std::endl;
  // do something : sort
  monitor.sow("sort vector");
  std::sort(vec.begin(), vec.end());
  // output the period of the last duration
  std::cout << monitor.reap("sort vector") << std::endl;
  // output the period of the total duration
  std::cout << monitor.reap("total cost") << std::endl;
  // sleep for 2s
  monitor.sow("sleep");
  ns_timer::sleep<DurationType::S>(2);
  std::cout << monitor.reap("sleep") << std::endl;
  return;
}

int main(int argc, char const *argv[]) {
  try {
    ::foo_timer();
    ::foo_timer_monitor();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
