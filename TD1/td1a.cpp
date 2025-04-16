#include <iostream>
#include "Chrono.h"

int main() {

    std::cout << "\n--- Testing timespec_now() and timespec_wait() ---" << std::endl;

    timespec time = timespec_now();
    std::cout << "Time: " << time << std::endl;

    timespec delay;
    delay.tv_sec = 3;
    delay.tv_nsec = 0;
    std::cout << "Waiting 3s..." << std::endl;
    timespec_wait(delay);
    time = timespec_now();
    
    std::cout << "Time after 3s: " << time << std::endl;

    //-----------------------------------------------------------------------------------

    std::cout << "\n--- Testing timespec_from_ms(), timespec_negate(), timespec_to_ms() and operator - ---" << std::endl;

    double time_in_ms = -12345678;
    timespec truth;
    truth.tv_sec = -12346;
    truth.tv_nsec = 1000000000-678000000;

    std::cout << "True time: " << truth << std::endl;

    timespec time_from_ms = timespec_from_ms(time_in_ms);
    std::cout << "Time from ms: " << time_from_ms << std::endl;

    timespec time_neg = timespec_negate(time_from_ms);
    std::cout << "Time negated: " << time_neg << std::endl;
    
    double time_back_in_ms = timespec_to_ms(time_neg);
    std::cout << "Time back to ms: " << time_back_in_ms << " ms" << std::endl;

    time_from_ms = timespec_from_ms(time_back_in_ms);
    std::cout << "Time from ms: " << time_from_ms << std::endl;

    time_neg = -time_from_ms;
    std::cout << "Time negated (with -): " << time_neg << std::endl;

    //-----------------------------------------------------------------------------------

    std::cout << "\n--- Testing timespec_add(), timespec_subtract() and its operators ---" << std::endl;
    
    timespec time1 = timespec_from_ms(987654321);
    timespec time2 = timespec_from_ms(-876543210);

    std::cout << "(Time 1: " << time1 << "   Time 2:" << time2 << ")" << std::endl;

    timespec time_sum = timespec_add(time1, time2);
    std::cout << "Time sum (add): " << time_sum << std::endl;
    time_sum = time1 + time2;
    std::cout << "Time sum (+): " << time_sum << std::endl;
    time1 += time2;
    std::cout << "Time sum (+=): " << time1 << std::endl;

    time1 = timespec_from_ms(987654321);
    timespec time_diff = timespec_subtract(time1, time2);
    std::cout << "Time diff (sub): " << time_diff << std::endl;
    time_diff = time1 - time2;
    std::cout << "Time diff (-): " << time_diff << std::endl;
    time1 -= time2;
    std::cout << "Time diff (-=): " << time1 << std::endl;
    
    time1 = timespec_from_ms(2700);
    time2 = timespec_from_ms(3500);

    std::cout << "(Time 1: " << time1 << "   Time 2:" << time2 << ")" << std::endl;

    time_sum = timespec_add(time1, time2);
    std::cout << "Time sum (add): " << time_sum << std::endl;
    time_sum = time1 + time2;
    std::cout << "Time sum (+): " << time_sum << std::endl;
    time1 += time2;
    std::cout << "Time sum (+=): " << time1 << std::endl;

    time1 = timespec_from_ms(2700);
    time_diff = timespec_subtract(time1, time2);
    std::cout << "Time diff (sub): " << time_diff << std::endl;
    time_diff = time1 - time2;
    std::cout << "Time diff (-): " << time_diff << std::endl;
    time1 -= time2;
    std::cout << "Time diff (-=): " << time1 << std::endl;

    //-----------------------------------------------------------------------------------

    std::cout << "\n--- Testing boolean operators ---" << std::endl;

    time1 = timespec_from_ms(2700);
    time2 = timespec_from_ms(3500);
    timespec time3;
    time3.tv_sec = 2;
    time3.tv_nsec = 700000000;

    std::cout << "Testing == (expecting false): " << (time1 == time2) << std::endl;
    std::cout << "Testing == (expecting true): " << (time1 == time3) << std::endl;
    std::cout << "Testing != (expecting true): " << (time1 != time2) << std::endl;
    std::cout << "Testing != (expecting false): " << (time1 != time3) << std::endl;
    std::cout << "Testing < (expecting true): " << (time1 < time2) << std::endl;
    std::cout << "Testing < (expecting false): " << (time1 < time3) << std::endl;
    std::cout << "Testing > (expecting false): " << (time1 > time2) << std::endl;
    std::cout << "Testing > (expecting true): " << (time1 > (time3 - time2)) << std::endl;

    return 0;
}