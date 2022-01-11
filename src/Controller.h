#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <I2Cdev.h>
#include "config.h"
#include "dataTypes.h"

class Controller{
    public:
        ControlOutput calculateControlOutput(State& _state, const State& _reference);
        
    private:
        const float dt{1000/LOOP_FREQUENCY};

        float ryPrev;
        float ryErrorInt;

        float xPrev;
        float xErrorInt;

        float velXPrev;
        float velXErrorInt;

};

#endif