#include "Chrono.h"

void Chrono::restart()
{
    m_startTime = timespec_now();
    m_stopTime = m_startTime;
}

Chrono::Chrono()
{
    restart();
}

void Chrono::stop()
{
    m_stopTime = timespec_now();
}

bool Chrono::isActive() const
{
    return m_startTime == m_stopTime;
}

timespec Chrono::lap() const
{

    if (isActive())
    {
        return timespec_now() - m_startTime;
    }
    else
    {
        return m_stopTime - m_startTime;
    }
}

double Chrono::lap_ms() const
{
    return timespec_to_ms(lap());
}