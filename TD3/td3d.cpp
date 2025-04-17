#include <iostream>
#include <stdlib.h>
#include "./Utils/Incrementer.h"
#include <vector>
#include <iomanip>

int main(int argc, char *argv[])
{

    Chrono chrono;

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " nLoops nTasks [protect=0] [policy=SCHED_OTHER]" << std::endl;
        return 1;
    }

    int nLoops = atoi(argv[1]);
    int nTasks = atoi(argv[2]);
    bool protect = false;
    int policy = SCHED_OTHER;

    if (argc > 3)
    {
        protect = atoi(argv[3]);
    }
    if (argc > 4)
    {
        policy = atoi(argv[4]);
    }

    Thread::setMainSched(policy);

    Counter counter(protect);

    std::vector<std::unique_ptr<Incrementer>> incrementers;
    std::vector<double> durations;

    for (int i = 0; i < nTasks; i++)
    {
        incrementers.push_back(std::make_unique<Incrementer>(i, counter, nLoops));
    }

    for (int i = 0; i < nTasks; i++)
    {
        incrementers[i]->start(Thread::getMaxPrio(policy));
        durations.push_back(chrono.lap_ms());
    }

    for (int i = 0; i < nTasks; i++)
    {
        incrementers[i]->join();
        durations[i] += incrementers[i]->duration_ms();
    }

    chrono.stop();

    std::cout << "Execution time: " << std::fixed << std::setprecision(1) << chrono.lap_ms() / 1000.0 << "s" << std::endl;
    for (int i = 0; i < nTasks; i++)
    {
        std::cout << "Task " << i << " duration: " << durations[i] << "ms" << std::endl;
    }
    std::cout << "Counter value: " << counter.value() << std::endl;
    std::cout << "Expected value: " << nLoops * nTasks << std::endl;
    std::cout << "Percentage of realised incrementations: " << 100 * counter.value() / (nLoops * nTasks) << "%" << std::endl;

    return 0;
}