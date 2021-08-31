# DurationTimer
<kbd>___DurationTimer___</kbd> is a c++ template class for timer. You can use it easily to count the ran time.This time statistics class provides two timing methods: <kbd>last Duration</kbd> and <kbd>total duration.</kbd> The detail ans example are below.
## Author
<kbd>___name___</kbd> ShuoLong Chen  
<kbd>___eamil___</kbd> 3079625093@qq.com
## Usage Example
<kbd>___Code___</kbd> 

```cpp
void foo()
{
    // define a timer
    DurationTimer<std::chrono::milliseconds> timer;
    // initialize the timer
    timer.init();
    // do something : generate elems and push_back to vec
    std::vector<int> vec;
    for (int i = 0; i != 100000; ++i)
    {
        vec.push_back(i);
    }
    // output the period of the last duration
    std::cout << timer.lastDurStr() << std::endl;
    // do something : shuffle
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine());
    // output the period of the last duration
    std::cout << timer.lastDurStr() << std::endl;
    // do something : sort
    std::sort(vec.begin(), vec.end());
    // output the period of the last duration
    std::cout << timer.lastDurStr() << std::endl;
    // output the period of the total duration
    std::cout << timer.totalDurStr() << std::endl;
    return;
}
```

## APIs
<kbd>constructor</kbd> 

```cpp
// the constructor
DurationTimer();

// template
// DurationTimer<_Tf,_C> timer;
// the _Tf is the time format for timing, such as std::chrono::milliseconds, std::chrono::minutes and so on.
// the _C is the clock used to timing, such as std::chrono::system_clock, std::chrono::high_resolution_clock, std::chrono::steady_clock.

// examples: 
DurationTimer<std::chrono::milliseconds> timer1;

DurationTimer<std::chrono::minutes, std::chrono::high_resolution_clock> timer2;

```
<kbd>init()</kbd> 

```cpp
// initialize the timer : public
template <typename _Tf, typename _C>
void DurationTimer<_Tf, _C>::init();
```
<kbd>lastDuration()</kbd> 

```cpp
// get the last duration : public
template <typename _Tf, typename _C>
int64_t DurationTimer<_Tf, _C>::lastDuration()
```
<kbd>totalDuration()</kbd> 

```cpp
// get the total duration : public
template <typename _Tf, typename _C>
int64_t DurationTimer<_Tf, _C>::totalDuration()
```
<kbd>lastDurStr()</kbd> 

```cpp
// get the last duration string exp : public
template <typename _Tf, typename _C>
std::string DurationTimer<_Tf, _C>::lastDurStr()
```
<kbd>totalDurStr()</kbd> 

```cpp
// get the total duration string exp : public
template <typename _Tf, typename _C>
std::string DurationTimer<_Tf, _C>::totalDurStr()
```
<kbd>getDuration(const TimePoint &ref)</kbd> 

```cpp
// get the duration between current and last time : protected
template <typename _Tf, typename _C>
int64_t DurationTimer<_Tf, _C>::getDuration(const TimePoint &ref)
```