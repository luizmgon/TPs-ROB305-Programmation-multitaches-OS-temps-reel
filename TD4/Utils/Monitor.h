#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>
#include "../../TD3/Utils/Mutex.h"

class Monitor
{

private:
    pthread_cond_t posixCondId;
    Mutex &m_mutex;

public:
    Monitor(Mutex &mutex);
    ~Monitor();
    void notify();
    void notifyAll();

    class Lock : public Mutex::Lock
    {
    private:
        Monitor &m_monitor;

    public:
        Lock(Monitor &monitor);
        Lock(Monitor &monitor, double timeout_ms);
        void wait();
        void wait(long timeout_ms);
    };
};

#endif // MONITOR_H