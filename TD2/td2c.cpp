#include <stdlib.h>
#include "./Utils/Looper.h"
#include "../TD1/Utils/Chrono.h"

int main(int argc, char* argv[]){

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_loops>" << std::endl;
        return 1;
    }

    double nLoops = atoi(argv[1]);
    Looper lp;

    Chrono c;
    double ret = lp.runLoop(nLoops);
    c.stop();

    std::cout << "Loops: " << ret << std::endl;
    std::cout << "Time: " << c.lap_ms() << " ms" << std::endl;
}