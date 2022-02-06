# DurationTimer

## Author
<kbd>___name___</kbd> ShuoLong Chen  
<kbd>___eamil___</kbd> 3079625093@qq.com

## OverView

<kbd>___DurationTimer___</kbd> is a c++ template class for timer. You can use it easily to count the ran time.This time statistics class provides two timing methods: <kbd>last Duration</kbd> and <kbd>total duration.</kbd> The detail ans example are below.  
And because it's a template class, you can just copy the head file and use it easily.

## Usage Example
<kbd>___Code___</kbd> 

```cpp
void foo()
{
    // define a timer
    Timer<std::chrono::system_clock> timer;
    // do something : generate elems and push_back to vec
    std::vector<int> vec;
    for (int i = 0; i != 100000; ++i)
        vec.push_back(i);
    // output the period of the last duration
    std::cout << timer.lastDurationStr<TimeUnit::ms>("create vector") << std::endl;
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
    return;
}
```
output
```log
# debug
{create vector: 3.888439(ms)}
{shuffle vector: 12.342250(ms)}
{sort vector: 30.742424(ms)}
{total cost: 46.995686(ms)}
{sleep: 2.000096(s)}

# release
{create vector: 1.025685(ms)}
{shuffle vector: 2.621002(ms)}
{sort vector: 9.609744(ms)}
{total cost: 13.280755(ms)}
{sleep: 2.000092(s)}
```

## APIs
<kbd>TimeUnit</kbd> 

```cpp
struct TimeUnit
{
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
```

<kbd>sleep(const typename DurationType::rep &period)</kbd>

```cpp
/**
 * @brief sleep for the 'period'
 *
 * @tparam DurationType the type of duration
 * @param period the time to sleep
 */
```

<kbd>Timer Constructor</kbd> 

```cpp
// the constructor
Timer<ClockType>();
/**
 * @brief the Timer class to timing
 * 
 * @tparam ClockType the type of the clock used, eg:std::chrono::system_clock
 */

// examples: 
DurationTimer<> default_timer;

DurationTimer<std::chrono::system_clock> sysc_timer;

DurationTimer<std::chrono::high_resolution_clock> hrc_timer;

DurationTimer<std::chrono::system_clock> sedc_timer;

```

<kbd>last_elapsed()</kbd> 

```cpp
/**
 * @brief get the last duration from the 'start' time point to 'now' time point
 * 
 * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
 * @return float the duration count
 */
```
<kbd>total_elapsed()</kbd> 

```cpp
/**
 * @brief get the total duration from the 'start' time point to 'now' time point
 * 
 * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
 * @return float the duration count
 */
```
<kbd>last_elapsed(const std::string &desc)</kbd> 

```cpp
/**
 * @brief get the last duration from the 'start' time point to 'now' time point
 * 
 * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
 * @param desc the describe of this duration
 * @return std::string the duration string
 */
```
<kbd>total_elapsed(const std::string &desc)</kbd> 

```cpp
/**
 * @brief get the total duration from the 'start' time point to 'now' time point
 * 
 * @tparam DurationType the type of std::duration, eg: std::chrono::milliseconds, std::chrono::seconds
 * @param desc the describe of this duration
 * @return std::string the duration string
 */
```
