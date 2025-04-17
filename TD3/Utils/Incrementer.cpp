#include "Incrementer.h"

Incrementer::Incrementer(int id, Counter &counter, double nLoops) : Thread(id), nLoops(nLoops), r_counter(counter) {}

void Incrementer::run()
{
    for (int i = 0; i < nLoops; i++)
    {
        r_counter.increment();
    }
}