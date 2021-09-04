#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <I2Cdev.h>
#include "baseController.h"
#include "config.h"

class PIDController : public BaseController{
    private:
        float dt = 1000/LOOP_FREQUENCY;
        float ryPrev;
        float ryErrorInt;

    public:
        ControlOutput calculateControlOutput(State _state, State _reference);
};

#endif