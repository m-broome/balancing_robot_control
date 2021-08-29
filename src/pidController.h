#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <I2Cdev.h>
#include "baseController.h"
#include "config.h"

class PIDController : public BaseController{
    private:
        double dt = 1000/LOOP_FREQUENCY;
        double ryPrev;
        double ryErrorInt;
        double limitIntegralWindup(double integralTerm);

    public:
        ControlOutput calculateControlOutput(State _state, State _reference);
};

#endif