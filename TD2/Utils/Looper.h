#ifndef LOOPER_H
#define LOOPER_H

class Looper
{
private:
    volatile bool doStop;
    double iLoop;

public:
    Looper() : doStop(false), iLoop(0) {}
    double runLoop(double nLoops);
    double getSample() const;
    double stopLoop();
};

#endif // LOOPER_H