#include "Timer.h"
#include "../../TD1/Utils/timespec.h"

Timer::Timer()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void *)this;

    timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer()
{
    timer_delete(tid);
}

void Timer::call_callback(int sig, siginfo_t *si, void *)
{
    auto p_timer = (Timer *)si->si_value.sival_ptr;
    p_timer->callback();
}

void Timer::start(timespec duration, bool isPeriodic)
{
    itimerspec its{{0, 0}, {0, 0}};
    its.it_value = duration;
    if (isPeriodic)
    {
        its.it_interval = duration;
    }

    timer_settime(tid, 0, &its, nullptr);
}

void Timer::start_ms(double duration_ms, bool isPeriodic)
{
    timespec duration = timespec_from_ms(duration_ms);
    start(duration, isPeriodic);
}

void Timer::stop()
{
    itimerspec its{{0, 0}, {0, 0}};
    timer_settime(tid, 0, &its, nullptr);
}
