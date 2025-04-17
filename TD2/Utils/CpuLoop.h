#ifndef CPU_LOOP_H
#define CPU_LOOP_H

#include "Calibrator.h"
#include "../../TD1/Utils/Chrono.h"

class CpuLoop : public Looper
{
private:
    Chrono c;
    Calibrator &calibrator;

public:
    CpuLoop(Calibrator &calibrator);
    double runTime(double duration_ms);
};

#endif // CPU_LOOP_H