#include "./Utils/Calibrator.h"
#include "../TD1/Utils/Chrono.h"

int main(int argc, char* argv[])
{
    Calibrator calibrator(200, 10);

    for (int desiredDuration = 500; desiredDuration <= 10000; desiredDuration += 200) {
        double nLoops = calibrator.nLoops(desiredDuration);

        Looper lp;
        Chrono c;
        lp.runLoop(nLoops);
        c.stop();

        std::cout << "Desired duration: " << desiredDuration << " ms" << std::endl;
        std::cout << "Real duration: " << c.lap_ms() << " ms" << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

}