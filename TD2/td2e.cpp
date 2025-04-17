#include "./Utils/CpuLoop.h"

int main(int argc, char* argv[])
{
    Calibrator calibrator(200, 10);
    CpuLoop cpuLoop(calibrator);

    double error;

    for (int runtime = 500; runtime <= 10000; runtime += 200) {
        error = cpuLoop.runTime(runtime);
        std::cout << "Desired duration: " << runtime << " ms" << std::endl;
        std::cout << "Relative error: " << error * 100 << "%" << std::endl;
    
        std::cout << "----------------------------------------" << std::endl;
    }
}