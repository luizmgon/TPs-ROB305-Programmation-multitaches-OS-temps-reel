#include "CountDown.h"
#include <iostream>

CountDown::CountDown(int n) : Timer(), counter(n + 1) {}

void CountDown::callback()
{

    if (counter > 0)
    {
        counter -= 1;
        std::cout << "Counter: " << counter << std::endl;
    }
    else
    {
        stop();
    }
}

int CountDown::getCounter() const
{
    return counter;
}
