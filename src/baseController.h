#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <I2Cdev.h>
#include "Drivers/imu.h"


class BaseController{
    public:
        virtual ControlOutput calculateControlOutput(State _state, State _reference) = 0;
};

#endif