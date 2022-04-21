#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>

namespace ns_timer {

#define THROW_EXCEPTION(where, what) \
  throw std::runtime_error(std::string("[ error from 'libtimer-'") + #where + "' ] " + what)

  namespace DurationType {
    struct NS : public std::chrono::nanoseconds {
      using chrono_type = std::chrono::nanoseconds;
      using chrono_type::chrono_type;
      static std::string unit_str() {
        return "NS";
      }
    };

    struct US : public std::chrono::microseconds {
      using chrono_type = std::chrono::microseconds;
      using chrono_type::chrono_type;
      static std::string unit_str() {
        return "US";
      }
    };

    struct MS : public std::chrono::milliseconds {
      using chrono_type = std::chrono::milliseconds;
      using chrono_type::chrono_type;
      static std::string unit_str() {
        return "MS";
      }
    };

    struct S : public std::chrono::seconds {
      using chrono_type = std::chrono::seconds;
      using chrono_type::chrono_type;
      static std::string unit_str() {
        return "S";
      }
    };

    struct MIN : public std::chrono::minutes {
      using chrono_type = std::chrono::minutes;
      using chrono_type::chrono_type;
      static std::string unit_str() {
        return "MIN";
      }
    };

    struct H : public std::chrono::hours {
      using chrono_type = std::chrono::hours;
      using chrono_type::chrono_type;
      static std::string unit_str() {
        return "H";
      }
    };

  } // namespace DurationType

  /**
   * @brief sleep for the 'period'
   *
   * @tparam DurationType the type of duration
   * @param period the time to sleep
   */
  template <typename DurationType = DurationType::MS>
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
  class _Timer_ {
  public:
    using default_dur_type = DurationType::MS;
    using clock_type = ClockType;
    using time_point_type = typename clock_type::time_point;
    using self_type = _Timer_<clock_type>;
    using Ptr = std::shared_ptr<self_type>;

  private:
    time_point_type _start;
    time_point_type _last;

  public:
    _Timer_() : _start(clock_type::now()), _last(clock_type::now()) {}

    static Ptr create() {
      return std::make_shared<self_type>();
    }

    /**
     * @brief get the last duration from the 'start' time point to 'now' time point
     *
     * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
     * @return float the duration count
     */
    template <typename DurationType = default_dur_type>
    float last_elapsed() {
      return this->count<DurationType>(this->_last);
    }

    /**
     * @brief get the total duration from the 'start' time point to 'now' time point
     *
     * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
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
     * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
     * @param desc the describe of this duration
     * @param prec the precision for float value
     * @return std::string the duration string
     */
    template <typename DurationType = default_dur_type>
    std::string last_elapsed(const std::string &desc, std::size_t prec = 5) {
      std::stringstream stream;
      stream << std::fixed << std::setprecision(prec);
      stream << "{'";
      stream << desc << "': " << this->last_elapsed<DurationType>();
      stream << '(' << DurationType::unit_str() << ')';
      stream << '}';
      return stream.str();
    }

    /**
     * @brief get the total duration from the 'start' time point to 'now' time point
     *
     * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
     * @param desc the describe of this duration
     * @param prec the precision for float value
     * @return std::string the duration string
     */
    template <typename DurationType = default_dur_type>
    std::string total_elapsed(const std::string &desc, std::size_t prec = 5) {
      std::stringstream stream;
      stream << std::fixed << std::setprecision(prec);
      stream << "{'";
      stream << desc << "': " << this->total_elapsed<DurationType>();
      stream << '(' << DurationType::unit_str() << ')';
      stream << '}';
      return stream.str();
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

    /**
     * @brief restart the timer
     */
    void re_start() {
      this->_last = clock_type::now();
      return;
    }

    /**
     * @brief reboot the timer
     */
    void re_boot() {
      this->_start = clock_type::now();
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
    _Timer_(const self_type &) = delete;
    _Timer_(self_type &&) = delete;
    self_type &operator=(const self_type &) = delete;
    self_type &operator=(self_type &&) = delete;
  };

  using Timer = _Timer_<std::chrono::system_clock>;

  template <class ClockType = std::chrono::system_clock>
  class _TimerMonitor_ {

  public:
    using default_dur_type = DurationType::MS;
    using clock_type = ClockType;

  private:
    using timer_type = _Timer_<clock_type>;
    using timer_ptr_type = typename timer_type::Ptr;
    using map_type = std::unordered_map<std::string, timer_ptr_type>;
    using self_type = _TimerMonitor_<clock_type>;

  public:
    using Ptr = std::shared_ptr<self_type>;

  private:
    map_type _timers;

  public:
    _TimerMonitor_() = default;

    /**
     * @brief create a timer monitor shared pointer
     */
    static Ptr create() {
      return std::make_shared<self_type>();
    }

    /**
     * @brief sow a seed to start timing
     *
     * @param id_str the string id of this timing event
     */
    self_type &sow(const std::string &id_str) {
      if (_timers.find(id_str) != _timers.end()) {
        THROW_EXCEPTION(TimerMonitor::sow, "You have sown the seed with '" + id_str + "'");
      }
      _timers.insert({id_str, timer_type::create()});
      return *this;
    }

    /**
     * @brief reap the result and delete the timing event
     *
     * @tparam DurationType the duration unit
     * @param id_str the string id of this timing event
     * @return float the count value
     */
    template <typename DurationType = default_dur_type>
    float reap(const std::string &id_str, float) {
      auto iter = this->get_timer_ptr(id_str);
      float dur = iter->second->template total_elapsed<default_dur_type>();
      _timers.erase(iter);
      return dur;
    }

    /**
     * @brief reap the result and delete the timing event
     *
     * @tparam DurationType the duration unit
     * @param id_str the string id of this timing event
     * @param prec the precision
     * @return std::string the formated string count value
     */
    template <typename DurationType = default_dur_type>
    std::string reap(const std::string &id_str, int prec = 5) {
      auto iter = this->get_timer_ptr(id_str);
      std::string dur = iter->second->template total_elapsed<default_dur_type>(id_str, prec);
      _timers.erase(iter);
      return dur;
    }

  protected:
    typename map_type::iterator get_timer_ptr(const std::string &id_str) {
      auto iter = _timers.find(id_str);
      if (iter == _timers.end()) {
        THROW_EXCEPTION(TimerMonitor::reap, "You have not sown the seed with '" + id_str + "'");
      }
      return iter;
    }

  private:
    _TimerMonitor_(const self_type &) = delete;
    _TimerMonitor_(self_type &&) = delete;
    self_type &operator=(const self_type &) = delete;
    self_type &operator=(self_type &&) = delete;
  };

  using TimerMonitor = _TimerMonitor_<std::chrono::system_clock>;

} // namespace ns_timer
