#include "Looper.h"
#include <cfloat>
#include <iostream>

double Looper::runLoop(double nLoops = DBL_MAX)
{
    iLoop = 0.0;
    
    while(!doStop && iLoop < nLoops)
    {
        iLoop += 1.0;
    }
    return iLoop;
}

double Looper::getSample() const
{
    return iLoop;
}

double Looper::stopLoop()
{
    doStop = true;
    return iLoop;
}