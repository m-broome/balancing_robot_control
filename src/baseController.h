#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <I2Cdev.h>
#include "Drivers/imu.h"

struct ControlOutput
{
    double leftSpeed;
    double rightSpeed;
};

class BaseController{
    private:

    public:
        virtual ControlOutput calculateControlOutput(State _state, State _reference) = 0;
};

#endif