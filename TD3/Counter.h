#ifndef COUNTER2_H
#define COUNTER2_H

#include "Mutex.h"
#include <memory>

class Counter
{
    private:
        double m_value;
        std::unique_ptr<Mutex> p_mutex;

    public:
        Counter(bool protect);
        double increment();
        double value() const;
        bool isProtected();

};

#endif // COUNTER2_H