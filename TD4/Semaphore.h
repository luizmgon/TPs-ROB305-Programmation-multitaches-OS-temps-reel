#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "../TD3/Mutex.h"
#include "Monitor.h"
#include <limits>

class Semaphore
{

    using CountType = unsigned long;

private:
    CountType counter;
    CountType maxCount;
    Mutex mutex;
    Monitor notEmpty;

public:
    Semaphore(CountType initValue = 0, CountType maxValue = std::numeric_limits<CountType>::max());

    void give();
    void take();
    bool take(long timeout_ms);
};

#endif // SEMAPHORE_H
