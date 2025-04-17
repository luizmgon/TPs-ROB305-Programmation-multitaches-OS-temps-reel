#include "./Utils/Thread.h"
#include "../TD2/Utils/CpuLoop.h"
#include "./Utils/Mutex.h"

double startTime = 0;

void log(const std::string &msg, const std::string &threadName)
{
    double now = timespec_to_ms(timespec_now()) - startTime;
    std::cout << "[" << now << " ms] " << threadName << ": " << msg << std::endl;
}

class Thread_A : public Thread
{
private:
    CpuLoop cpuLoop;
    Mutex &ressource;

public:
    Thread_A(Calibrator &calibrator, Mutex &ressource) : Thread(0), cpuLoop(calibrator), ressource(ressource) {}
    void run() override
    {
        int policy;
        sched_param param;
        pthread_getschedparam(pthread_self(), &policy, &param);
        log("Running with policy = " + std::string(policy == SCHED_FIFO ? "SCHED_FIFO" : "SCHED_OTHER") +
                ", priority = " + std::to_string(param.sched_priority),
            "Thread A");
        double t0 = timespec_to_ms(timespec_now()) - startTime;
        cpuLoop.runTime(1000);
        double t1 = timespec_to_ms(timespec_now()) - startTime;
        log("runTime(1000) durou " + std::to_string(t1 - t0) + "ms", "Thread A");
        log("asked the mutex", "Thread A");
        {
            Mutex::Lock lock(ressource);
            log("got the mutex", "Thread A");
            cpuLoop.runTime(1000);
        }
        log("released the mutex", "Thread A");
        cpuLoop.runTime(2000);
        log("finished", "Thread A");
    }
};

class Thread_B : public Thread
{
private:
    CpuLoop cpuLoop;

public:
    Thread_B(Calibrator &calibrator) : Thread(1), cpuLoop(calibrator) {}
    void run() override
    {
        int policy;
        sched_param param;
        pthread_getschedparam(pthread_self(), &policy, &param);
        log("Running with policy = " + std::string(policy == SCHED_FIFO ? "SCHED_FIFO" : "SCHED_OTHER") +
                ", priority = " + std::to_string(param.sched_priority),
            "Thread B");
        cpuLoop.runTime(1000);
        log("finished", "Thread B");
    }
};

class Thread_C : public Thread
{
private:
    CpuLoop cpuLoop;
    Mutex &ressource;

public:
    Thread_C(Calibrator &calibrator, Mutex &ressource) : Thread(2), cpuLoop(calibrator), ressource(ressource) {}
    void run() override
    {
        int policy;
        sched_param param;
        pthread_getschedparam(pthread_self(), &policy, &param);
        log("Running with policy = " + std::string(policy == SCHED_FIFO ? "SCHED_FIFO" : "SCHED_OTHER") +
                ", priority = " + std::to_string(param.sched_priority),
            "Thread C");
        cpuLoop.runTime(2000);
        log("asked the mutex", "Thread C");
        {
            Mutex::Lock lock(ressource);
            log("got the mutex", "Thread C");
            cpuLoop.runTime(2000);
        }
        log("released the mutex", "Thread C");
        cpuLoop.runTime(1000);
        log("finished", "Thread C");
    }
};

int main()
{
    Thread::setMainSched(SCHED_FIFO);
    sched_param param;
    pthread_getschedparam(pthread_self(), &param.sched_priority, &param);
    std::cout << "Main thread policy = " << (param.sched_priority == SCHED_FIFO ? "SCHED_FIFO" : "SCHED_OTHER") << std::endl;
    std::cout << "Main thread priority = " << param.sched_priority << std::endl;
    Calibrator calibrator(200, 10);
    Mutex ressource(true);
    Thread_A threadA(calibrator, ressource);
    Thread_B threadB(calibrator);
    Thread_C threadC(calibrator, ressource);

    startTime = timespec_to_ms(timespec_now());

    std::cout << "\n=== Iniciando execução ===" << std::endl;

    log("Calling Thread C", "main");
    threadC.start(Thread::getMaxPrio(SCHED_FIFO) - 3);

    usleep(3000000); // 3000ms

    log("Calling Thread A", "main");
    threadA.start(Thread::getMaxPrio(SCHED_FIFO) - 1);

    log("Calling Thread B", "main");
    threadB.start(Thread::getMaxPrio(SCHED_FIFO) - 2);

    threadC.join();
    threadA.join();
    threadB.join();

    double endTime = timespec_to_ms(timespec_now());
    double elapsedTime = endTime - startTime;
    std::cout << "\n=== Execução finalizada ===" << std::endl;
    std::cout << "Total elapsed time: " << elapsedTime << " ms" << std::endl;

    std::cout << "Thread A duration: " << threadA.duration_ms() << " ms" << std::endl;
    std::cout << "Thread B duration: " << threadB.duration_ms() << " ms" << std::endl;
    std::cout << "Thread C duration: " << threadC.duration_ms() << " ms" << std::endl;
}
