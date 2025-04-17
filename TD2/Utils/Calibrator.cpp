#include "Calibrator.h"
#include "Looper.h"
#include <cfloat>

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples) : nSamples(nSamples)
{

    start_ms(samplingPeriod_ms, true);
    lp.runLoop(DBL_MAX);

    // Calculate a and b for the linear regression
    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;

    for (unsigned i = 1; i <= nSamples; i++)
    {
        sumX += i * samplingPeriod_ms;
        sumY += samples[i - 1];
        sumXY += i * samplingPeriod_ms * samples[i - 1];
        sumX2 += i * samplingPeriod_ms * i * samplingPeriod_ms;
    }

    a = (nSamples * sumXY - sumX * sumY) / (nSamples * sumX2 - sumX * sumX);
    b = (sumY - a * sumX) / nSamples;

    // std::cout << "a: " << a << std::endl;
    // std::cout << "b: " << b << std::endl;
}

void Calibrator::callback()
{
    samples.push_back(lp.getSample());

    if (samples.size() == nSamples)
    {
        lp.stopLoop();
        stop();
    }
}

double Calibrator::nLoops(double duration_ms)
{
    return a * duration_ms + b;
}