#pragma once

#include <chrono>
#include <iostream>
#include <string>
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
};

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
  float lastDuration() {
    return this->getCount<DurationType>(this->_last);
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
  float totalDuration() {
    return this->getCount<DurationType>(this->_start);
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
  std::string lastDurationStr(const std::string &desc = "lastDur") {
    std::string str;
    str += '{';
    str += desc + ": " + std::to_string(this->lastDuration<DurationType>()) +
           this->getTimerUnit<DurationType>();
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
  std::string totalDurationStr(const std::string &desc = "totalDur") {
    std::string str;
    str += '{';
    str += desc + ": " + std::to_string(this->totalDuration<DurationType>()) +
           this->getTimerUnit<DurationType>();
    str += '}';
    return str;
  }

 protected:
  /**
   * @brief Get the time unit for the duration type
   *
   * @tparam DurationType the type of std::duration
   * @return std::string the unit string
   */
  template <typename DurationType = default_dur_type>
  std::string getTimerUnit() const {
    if (std::is_same<DurationType, std::chrono::nanoseconds>::value)
      return "(ns)";
    else if (std::is_same<DurationType, std::chrono::microseconds>::value)
      return "(us)";
    else if (std::is_same<DurationType, std::chrono::milliseconds>::value)
      return "(ms)";
    else if (std::is_same<DurationType, std::chrono::seconds>::value)
      return "(s)";
    else if (std::is_same<DurationType, std::chrono::minutes>::value)
      return "(min)";
    else if (std::is_same<DurationType, std::chrono::hours>::value)
      return "(h)";
    return "";
  }

  /**
   * @brief Get the timer's count
   *
   * @tparam DurationType the type of std::duration
   * @param ref the reference duration to count. eg: this->_start, this->_last
   * @return float the count value
   */
  template <typename DurationType = default_dur_type>
  float getCount(const time_point_type &ref) {
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
