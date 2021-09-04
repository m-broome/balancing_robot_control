#ifndef BASEMOTORCONTROLLER_H
#define BASEMOTORCONTROLLER_H

# include <AccelStepper.h>
# include "../baseController.h"


class BaseMotorController
{
    protected:
        AccelStepper motor;
        int motorDir;
        int microsteps;

    public:
        virtual void initialiseController() = 0;

        virtual void applyControl(ControlOutput controlOutput) = 0;
        
        void setSpeed(float speed);
        
        void run();

};

# endif