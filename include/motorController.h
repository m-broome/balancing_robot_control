#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <AccelStepper.h>


class MotorController
{
    protected:
        AccelStepper motor;

        int motorDir;

        int microsteps;

        float maxSpeed;
        
        float maxAcceleration;

    public:        
        MotorController(int StpPin, int DirPin, float maxSpeed, float maxAcceleration, int motorDir, int microsteps);

        MotorController();
        
        void setSpeed(const float& speed);
        
        void run();
};

#endif