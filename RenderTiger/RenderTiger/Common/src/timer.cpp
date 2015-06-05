#include "timer.h"

#include <windows.h>

timer::timer()
:_start_time(0) {
    __int64 f;
    QueryPerformanceFrequency((LARGE_INTEGER*)&f);
    _seconds_per_count = 1.0f / (float)f;
}

timer::~timer() {

}

void timer::start() {
    QueryPerformanceCounter((LARGE_INTEGER*)&_start_time);
}

float timer::stop() const {
    __int64 now;
    QueryPerformanceCounter((LARGE_INTEGER*)&now);
    return (now - _start_time) * _seconds_per_count;
}

float timer::get_time_since_start() const {
    return stop();
}