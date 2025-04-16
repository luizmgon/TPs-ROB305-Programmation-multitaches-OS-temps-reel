#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include "Timer.h"
#include "timespec.h"
#include <vector>
#include "Looper.h"

class Calibrator : public Timer
{
    private:
        double a;
        double b;
        std::vector<double> samples;
        Looper lp;
        unsigned nSamples;

    public: 
        Calibrator(double samplingPeriod_ms, unsigned nSamples);
        double nLoops(double duration_ms);

    private:
        void callback() override;
};

#endif // CALIBRATOR_H