#ifndef TIMER_H
#define TIMER_H

#include "Wire.h"
#include <TimeLib.h>

class Timer{

    private:
        float startt;
        float elapsedt;

    public:
        void start();
        void reset();
        void getElapsed(float& dt);
};

#endif