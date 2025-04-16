#include "CpuLoop.h"
#include <iostream>
#include "../TD1/Chrono.h"

CpuLoop::CpuLoop(Calibrator& calibrator) : calibrator(calibrator) {}

double CpuLoop::runTime(double duration_ms) {

    double nLoops = calibrator.nLoops(duration_ms);

    c.restart();
    runLoop(nLoops);

    double error = (c.lap_ms() - duration_ms) / duration_ms;

    return error;
}