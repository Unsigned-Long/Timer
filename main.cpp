#include <algorithm>
#include <random>
#include <vector>

#include "timer.h"

using namespace ns_timer;

void foo() {
  // define a timer
  Timer<std::chrono::system_clock> timer;
  // do something : generate elems and push_back to vec
  std::vector<int> vec;
  for (int i = 0; i != 100000; ++i) vec.push_back(i);
  // output the period of the last duration
  std::cout << timer.lastDurationStr<TimeUnit::ms>("create vector")
            << std::endl;
  // do something : shuffle
  std::shuffle(vec.begin(), vec.end(), std::default_random_engine());
  // output the period of the last duration
  std::cout << timer.lastDurationStr("shuffle vector") << std::endl;
  // do something : sort
  std::sort(vec.begin(), vec.end());
  // output the period of the last duration
  std::cout << timer.lastDurationStr("sort vector") << std::endl;
  // output the period of the total duration
  std::cout << timer.totalDurationStr("total cost") << std::endl;
  // sleep for 2s
  ns_timer::sleep<ns_timer::TimeUnit::s>(2);
  std::cout << timer.lastDurationStr<ns_timer::TimeUnit::s>("sleep") << std::endl;
  return;
}

int main(int argc, char const* argv[]) {
  ::foo();
  return 0;
}
