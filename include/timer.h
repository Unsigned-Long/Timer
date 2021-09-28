#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <type_traits>

namespace ns_timer
{
    // a template class for duration time print
    template <typename _Tf = std::chrono::milliseconds, typename _C = std::chrono::steady_clock>
    class DurationTimer
    {
    public:
        typedef _C Clock;
        typedef _Tf TimeFormat;
        typedef typename _C::time_point TimePoint;

    private:
        TimePoint _last;
        TimePoint _start;
        std::string _stad;

    public:
        DurationTimer();
        void init();

        int64_t lastDuration();
        int64_t totalDuration();

        std::string lastDurStr(const std::string &describe = "last_Dur");
        std::string totalDurStr(const std::string &describe = "total_Dur");

    protected:
        int64_t getDuration(const TimePoint &ref);
    };

    template <typename _Tf, typename _C>
    DurationTimer<_Tf, _C>::DurationTimer()
    {
        if (true == std::is_same<TimeFormat, std::chrono::microseconds>::value)
            this->_stad = " us";
        if (true == std::is_same<TimeFormat, std::chrono::milliseconds>::value)
            this->_stad = " ms";
        if (true == std::is_same<TimeFormat, std::chrono::seconds>::value)
            this->_stad = " s";
        if (true == std::is_same<TimeFormat, std::chrono::minutes>::value)
            this->_stad = " m";
        if (true == std::is_same<TimeFormat, std::chrono::hours>::value)
            this->_stad = " h";
    }

    template <typename _Tf, typename _C>
    void DurationTimer<_Tf, _C>::init()
    {
        this->_start = Clock::now();
        this->_last = Clock::now();
        return;
    }

    template <typename _Tf, typename _C>
    int64_t DurationTimer<_Tf, _C>::lastDuration()
    {
        return this->getDuration(this->_last);
    }

    template <typename _Tf, typename _C>
    int64_t DurationTimer<_Tf, _C>::totalDuration()
    {
        return this->getDuration(this->_start);
    }

    template <typename _Tf, typename _C>
    std::string DurationTimer<_Tf, _C>::lastDurStr(const std::string &describe)
    {
        auto dur = this->lastDuration();
        std::string str = describe + '{';
        str += std::to_string(dur) + this->_stad + '}';
        return str;
    }

    template <typename _Tf, typename _C>
    std::string DurationTimer<_Tf, _C>::totalDurStr(const std::string &describe)
    {
        auto dur = this->totalDuration();
        std::string str = describe + '{';
        str += std::to_string(dur) + this->_stad + '}';
        return str;
    }

    template <typename _Tf, typename _C>
    int64_t DurationTimer<_Tf, _C>::getDuration(const TimePoint &ref)
    {
        auto cur = Clock::now();
        auto duration = std::chrono::duration_cast<TimeFormat>(cur - ref).count();
        this->_last = cur;
        return duration;
    }

    void foo();
} // namespace ns_test
