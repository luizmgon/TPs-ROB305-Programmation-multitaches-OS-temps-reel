#ifndef CHRONO_H
#define CHRONO_H

#include "timespec.h"

class Chrono
{
private:
    timespec m_startTime;
    timespec m_stopTime;

public:
    Chrono();
    void stop();
    void restart();
    bool isActive() const;
    timespec lap() const;
    double lap_ms() const;
};

#endif // CHRONO_H