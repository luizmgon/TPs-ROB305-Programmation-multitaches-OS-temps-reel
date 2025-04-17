#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include "../../TD1/Utils/Chrono.h"

class Thread
{
private:
    pthread_t posixThreadId;
    pthread_attr_t posixThreadAttrId;
    Chrono m_chrono;

public:
    int id;

public:
    Thread(int id);
    virtual ~Thread();
    void start(int priority);
    void join();

    bool isStarted() const;
    long duration_ms() const;

protected:
    virtual void run() = 0;

public:
    static void *call_run(void *v_thread);
    static int getMaxPrio(int policy);
    static int getMinPrio(int policy);
    static void setMainSched(int policy);
    static int getMainSched();
};

#endif // THREAD_H