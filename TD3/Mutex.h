#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex{

    friend class Monitor;

    private:
        pthread_mutex_t posixMutexId;
        pthread_mutexattr_t posixMutexAttrId;

    public:
        Mutex(bool isInversionSafe);
        ~Mutex();

    private:
        void lock();
        bool lock(double timeout_ms);
        void unlock();

    public:
        class Lock{
            private:
                Mutex& m_mutex;
            public:
                Lock(Mutex& mutex);
                Lock(Mutex& mutex, double timeout_ms);
                ~Lock();
        };

};

#endif // MUTEX_H