#include "Mutex.h"
#include "../TD1/timespec.h"
#include "TimeoutException.cpp"

Mutex::Mutex(bool isInversionSafe = false)
{
    pthread_mutexattr_init(&posixMutexAttrId);

    if(isInversionSafe)
    {    
        // pthread_mutexattr_settype(&posixMutexAttrId, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutexattr_setprotocol(&posixMutexAttrId, PTHREAD_PRIO_INHERIT);
    }

    pthread_mutex_init(&posixMutexId, &posixMutexAttrId);
}


Mutex::~Mutex()
{
    pthread_mutex_destroy(&posixMutexId);
}

void Mutex::lock()
{
    pthread_mutex_lock(&posixMutexId);
}

bool Mutex::lock(double timeout_ms)
{
    timespec deadline = timespec_now() + timespec_from_ms(timeout_ms);
    return pthread_mutex_timedlock(&posixMutexId, &deadline) == 0;

}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixMutexId);
}

Mutex::Lock::Lock(Mutex& mutex) : m_mutex(mutex)
{
    m_mutex.lock();
}

Mutex::Lock::Lock(Mutex& mutex, double timeout_ms) : m_mutex(mutex)
{
    if(!m_mutex.lock(timeout_ms))
    {
        throw TimeoutException(timeout_ms);
    }
}

Mutex::Lock::~Lock()
{
    m_mutex.unlock();
}