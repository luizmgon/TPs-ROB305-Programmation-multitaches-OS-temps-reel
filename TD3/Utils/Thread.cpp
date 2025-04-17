#include "Thread.h"

Thread::Thread(int id) : id(id)
{
    pthread_attr_init(&posixThreadAttrId);
}

Thread::~Thread()
{
    pthread_attr_destroy(&posixThreadAttrId);
}

void Thread::start(int priority)
{
    m_chrono.restart();
    sched_param sched;

    int policy = getMainSched();
    pthread_attr_setschedpolicy(&posixThreadAttrId, policy);

    sched.sched_priority = priority;

    pthread_attr_setschedparam(&posixThreadAttrId, &sched);
    pthread_attr_setinheritsched(&posixThreadAttrId, PTHREAD_EXPLICIT_SCHED);

    pthread_create(&posixThreadId, &posixThreadAttrId, call_run, this);
}

void Thread::join()
{
    pthread_join(posixThreadId, NULL);
}

bool Thread::isStarted() const
{
    return m_chrono.isActive();
}

long Thread::duration_ms() const
{
    return m_chrono.lap_ms();
}

void *Thread::call_run(void *v_thread)
{
    Thread *thread = (Thread *)v_thread;
    thread->run();
    thread->m_chrono.stop();

    return v_thread;
}

void Thread::setMainSched(int policy)
{
    struct sched_param schedParam;

    schedParam.sched_priority = policy == SCHED_OTHER ? 0 : sched_get_priority_max(policy);

    pthread_setschedparam(pthread_self(), policy, &schedParam);
}

int Thread::getMainSched()
{
    struct sched_param schedParam;
    int policy;

    pthread_getschedparam(pthread_self(), &policy, &schedParam);

    return policy;
}

int Thread::getMaxPrio(int policy)
{
    return sched_get_priority_max(policy);
}

int Thread::getMinPrio(int policy)
{
    return sched_get_priority_min(policy);
}