#include "timespec.h"
#include <cmath>

double timespec_to_ms(const timespec& time_ts) {

    return time_ts.tv_sec * 1000.0 + time_ts.tv_nsec / 1000000.0;

}

timespec timespec_from_ms(double time_ms){

    timespec time;
    time.tv_sec = static_cast<time_t>(time_ms / 1000);
    time.tv_nsec = std::lround((time_ms - time.tv_sec * 1000) * 1000000);

    if(time.tv_nsec < 0){
        time.tv_nsec += 1000000000;
        time.tv_sec--;
    }

    return time;

}

timespec timespec_now(){

    timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return time;

}

timespec timespec_negate(const timespec& time_ts){

    timespec time;

    time.tv_sec = -time_ts.tv_sec;
    time.tv_nsec = -time_ts.tv_nsec;

    if(time.tv_nsec < 0){
        time.tv_nsec += 1000000000;
        time.tv_sec--;
    }

    return time;
    
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts){

    timespec result;
    result.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    result.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;

    if(result.tv_nsec >= 1000000000){
        result.tv_sec++;
        result.tv_nsec -= 1000000000;
    }

    return result;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts){

    timespec time2neg = timespec_negate(time2_ts);
    return timespec_add(time1_ts, time2neg);

}

void timespec_wait(const timespec& delay_ts){

    timespec rem;
    timespec delay_ts_copy = delay_ts;

    while(nanosleep(&delay_ts_copy, &rem) == -1){
        delay_ts_copy = rem;
    }

}

timespec operator- (const timespec& time_ts){

    return timespec_negate(time_ts);

}

timespec operator+ (const timespec& time1_ts, const timespec& time2_ts){

    return timespec_add(time1_ts, time2_ts);

}

timespec operator- (const timespec& time1_ts, const timespec& time2_ts){

    return timespec_subtract(time1_ts, time2_ts);

}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts){

    time_ts = time_ts + delay_ts;
    return time_ts;

}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts){

    time_ts = time_ts - delay_ts;
    return time_ts;

}

bool operator== (const timespec& time1_ts, const timespec& time2_ts){

    return time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec == time2_ts.tv_nsec;

}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts){

    return !(time1_ts == time2_ts);

}

bool operator< (const timespec& time1_ts, const timespec& time2_ts){

    if(time1_ts.tv_sec < time2_ts.tv_sec){
        return true;
    } else if(time1_ts.tv_sec == time2_ts.tv_sec){
        return time1_ts.tv_nsec < time2_ts.tv_nsec;
    } else {
        return false;
    }

}

bool operator> (const timespec& time1_ts, const timespec& time2_ts){

    return time2_ts < time1_ts;

}

std::ostream& operator<< (std::ostream& os, const timespec& time_ts){

    os << time_ts.tv_sec << " s " << time_ts.tv_nsec << " ns";
    return os;

}


