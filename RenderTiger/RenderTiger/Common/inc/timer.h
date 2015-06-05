#ifndef timer_h
#define timer_h

class timer {
public:
    timer();
    ~timer();
public:
    void  start();
    float stop() const;
    float get_time_since_start() const;
public:
    __int64 _start_time;
    float _seconds_per_count;
};

#endif