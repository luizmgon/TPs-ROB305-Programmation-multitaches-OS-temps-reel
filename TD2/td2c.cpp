#include <stdlib.h>
#include "Looper.h"
#include "../TD1/Chrono.h"

int main(int argc, char* argv[]){

    double nLoops = atoi(argv[1]);
    Looper lp;

    Chrono c;
    double ret = lp.runLoop(nLoops);
    c.stop();

    std::cout << "Loops: " << ret << std::endl;
    std::cout << "Time: " << c.lap_ms() << " ms" << std::endl;
}