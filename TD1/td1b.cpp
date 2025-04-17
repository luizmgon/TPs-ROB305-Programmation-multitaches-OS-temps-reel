#include <iostream>
#include "./Utils/Chrono.h"

int main()
{
    std::cout << "\n --- Testing Chrono ---" << std::endl;

    Chrono chrono;
    std::cout << "Chrono is active: " << chrono.isActive() << std::endl;
    std::cout << "Waiting 1s...\n"
              << std::endl;
    timespec_wait(timespec_from_ms(1000));

    timespec lap = chrono.lap();
    std::cout << "Lap: " << lap << std::endl;

    std::cout << "\nWaiting 1s...\n"
              << std::endl;
    timespec_wait(timespec_from_ms(1000));

    double lap_ms = chrono.lap_ms();
    std::cout << "Lap in ms: " << lap_ms << std::endl;

    std::cout << "\nWaiting 1s..." << std::endl;
    timespec_wait(timespec_from_ms(1000));
    std::cout << "Stopping..." << std::endl;

    chrono.stop();
    lap = chrono.lap();

    std::cout << "Chrono is active: " << chrono.isActive() << std::endl;
    std::cout << "Lap after stop: " << lap << std::endl;

    std::cout << "\nWaiting 1s...\n"
              << std::endl;
    timespec_wait(timespec_from_ms(1000));

    lap = chrono.lap();
    std::cout << "Lap 1s after stop: " << lap << std::endl;

    std::cout << "\nRestarting..." << std::endl;
    chrono.restart();
    chrono.stop();
    lap = chrono.lap();
    lap_ms = chrono.lap_ms();
    std::cout << "Shortest possible lap: " << lap << " = " << lap_ms << " ms" << std::endl;

    return 0;
}