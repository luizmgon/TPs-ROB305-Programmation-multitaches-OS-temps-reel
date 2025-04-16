#ifndef INCREMENTER_H
#define INCREMENTER_H

#include "Thread.h"
#include "Counter.h"

class Incrementer : public Thread {
    private:
        const double nLoops;
        Counter& r_counter;

    public:
        Incrementer(int id, Counter& counter, double nLoops);
    
    protected:
        void run() override;
};

#endif // INCREMENTER_H