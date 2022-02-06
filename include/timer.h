#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <type_traits>

namespace ns_timer {

struct TimeUnit {
 public:
  /**
   * @brief time units in the std::chrono
   */
  using ns = std::chrono::nanoseconds;
  using us = std::chrono::microseconds;
  using ms = std::chrono::milliseconds;
  using s = std::chrono::seconds;
  using min = std::chrono::minutes;
  using h = std::chrono::hours;

 protected:
  template <typename ClockType>
  friend class Timer;
  /**
   * @brief Get the time unit for the duration type
   *
   * @tparam DurationType the type of std::duration
   * @return std::string the unit string
   */
  template <typename DurationType>
  static std::string timeunit_str() {
    if (std::is_same<DurationType, TimeUnit::ns>::value)
      return "(ns)";
    else if (std::is_same<DurationType, TimeUnit::us>::value)
      return "(us)";
    else if (std::is_same<DurationType, TimeUnit::ms>::value)
      return "(ms)";
    else if (std::is_same<DurationType, TimeUnit::s>::value)
      return "(s)";
    else if (std::is_same<DurationType, TimeUnit::min>::value)
      return "(min)";
    else if (std::is_same<DurationType, TimeUnit::h>::value)
      return "(h)";
    return "";
  }

 private:
  TimeUnit() = delete;
};

/**
 * @brief sleep for the 'period'
 *
 * @tparam DurationType the type of duration
 * @param period the time to sleep
 */
template <typename DurationType = std::chrono::milliseconds>
void sleep(const typename DurationType::rep &period) {
  std::this_thread::sleep_for(DurationType(period));
  return;
}

/**
 * @brief the Timer class to timing
 *
 * @tparam ClockType the type of the clock used, eg:std::chrono::system_clock
 */
template <typename ClockType = std::chrono::system_clock>
class Timer {
 public:
  using default_dur_type = std::chrono::milliseconds;
  using clock_type = ClockType;
  using time_point_type = typename clock_type::time_point;

 private:
  const time_point_type _start;
  time_point_type _last;

 public:
  Timer() : _start(clock_type::now()), _last(clock_type::now()) {}

  /**
   * @brief get the last duration from the 'start' time point to 'now' time
   * point
   *
   * @tparam DurationType the type of std::duration, eg:
   * std::chrono::milliseconds, std::chrono::seconds
   * @return float the duration count
   */
  template <typename DurationType = default_dur_type>
  float last_elapsed() {
    return this->count<DurationType>(this->_last);
  }

  /**
   * @brief get the total duration from the 'start' time point to 'now' time
   * point
   *
   * @tparam DurationType the type of std::duration, eg:
   * std::chrono::milliseconds, std::chrono::seconds
   * @return float the duration count
   */
  template <typename DurationType = default_dur_type>
  float total_elapsed() {
    return this->count<DurationType>(this->_start);
  }

  /**
   * @brief get the last duration from the 'start' time point to 'now' time
   * point
   *
   * @tparam DurationType the type of std::duration, eg:
   * std::chrono::milliseconds, std::chrono::seconds
   * @param desc the describe of this duration
   * @return std::string the duration string
   */
  template <typename DurationType = default_dur_type>
  std::string last_elapsed(const std::string &desc) {
    std::string str;
    str += '{';
    str += desc + ": " + std::to_string(this->last_elapsed<DurationType>()) +
           TimeUnit::timeunit_str<DurationType>();
    str += '}';
    return str;
  }

  /**
   * @brief get the total duration from the 'start' time point to 'now' time
   * point
   *
   * @tparam DurationType the type of std::duration, eg:
   * std::chrono::milliseconds, std::chrono::seconds
   * @param desc the describe of this duration
   * @return std::string the duration string
   */
  template <typename DurationType = default_dur_type>
  std::string total_elapsed(const std::string &desc) {
    std::string str;
    str += '{';
    str += desc + ": " + std::to_string(this->total_elapsed<DurationType>()) +
           TimeUnit::timeunit_str<DurationType>();
    str += '}';
    return str;
  }

  /**
   * @brief sleep for the 'period'
   *
   * @tparam DurationType the type of duration
   * @param period the time to sleep
   */
  template <typename DurationType = default_dur_type>
  void sleep(const typename DurationType::rep &period) {
    std::this_thread::sleep_for(DurationType(period));
    return;
  }

 protected:
  /**
   * @brief Get the timer's count
   *
   * @tparam DurationType the type of std::duration
   * @param ref the reference duration to count. eg: this->_start, this->_last
   * @return float the count value
   */
  template <typename DurationType = default_dur_type>
  float count(const time_point_type &ref) {
    using cast_type =
        std::chrono::duration<float, typename DurationType::period>;
    auto dur = std::chrono::duration_cast<cast_type>(clock_type::now() - ref);
    this->_last = clock_type::now();
    return dur.count();
  }

 private:
  Timer(const Timer &) = delete;
  Timer(Timer &&) = delete;
  Timer &operator=(const Timer &) = delete;
};

}  // namespace ns_timer
