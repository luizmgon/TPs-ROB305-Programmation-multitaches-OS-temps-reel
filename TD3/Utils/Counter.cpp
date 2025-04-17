#include "Counter.h"

Counter::Counter(bool protect) : m_value(0), p_mutex(protect ? std::make_unique<Mutex>(false) : nullptr) {}

double Counter::increment()
{
    if (isProtected())
    {
        Mutex::Lock lock(*p_mutex);
        m_value++;
    }
    else
    {
        m_value++;
    }
    return m_value;
}

bool Counter::isProtected()
{
    return p_mutex != nullptr;
}

double Counter::value() const
{
    return m_value;
}