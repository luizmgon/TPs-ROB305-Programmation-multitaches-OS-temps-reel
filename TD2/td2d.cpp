#include "Calibrator.h"
#include "../TD1/Chrono.h"

int main(int argc, char* argv[])
{
    Calibrator calibrator(200, 10);

    int desiredDuration = 1250;
    double nLoops = calibrator.nLoops(desiredDuration);

    Looper lp;
    Chrono c;
    lp.runLoop(nLoops);
    c.stop();

    std::cout << "Desired duration: " << desiredDuration << " ms" << std::endl;
    std::cout << "Real duration: " << c.lap_ms() << " ms" << std::endl; 

}