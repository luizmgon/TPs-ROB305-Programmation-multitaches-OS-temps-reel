#include "Semaphore.h"

Semaphore::Semaphore(CountType initValue, CountType maxValue)
    : counter(initValue),
      maxCount(maxValue),
      mutex(false),
      notEmpty(mutex)
{
}

void Semaphore::give()
{
    Monitor::Lock lock(notEmpty);
    if (counter < maxCount)
    {
        ++counter;
        notEmpty.notify();
    }
}

void Semaphore::take()
{
    Monitor::Lock lock(notEmpty);
    while (counter == 0)
    {
        lock.wait();
    }
    --counter;
}

bool Semaphore::take(long timeout_ms)
{
    Monitor::Lock lock(notEmpty, timeout_ms);
    while (counter == 0)
    {
        lock.wait(timeout_ms);
        if (counter == 0)
            return false; // timeout
    }
    --counter;
    return true;
}
