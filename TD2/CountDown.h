#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include "Timer.h"

class CountDown : public Timer
{
    private:
        int counter;
    protected:
        void callback() override;
    public:
        CountDown(int n);
        int getCounter() const;
};

#endif // COUNTDOWN_H