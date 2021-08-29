#ifndef TIMER_H
#define TIMER_H

#include "Wire.h"
#include <TimeLib.h>

class Timer{

    private:
        double startt;
        double elapsedt;

    public:
        void start();
        void reset();
        void getElapsed(double& dt);
};

#endif