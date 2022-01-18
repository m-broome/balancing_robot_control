#ifndef ROBOT_H
#define ROBOT_H

#include "imu.h"
#include "motorController.h"
#include "Controller.h"
#include "dataTypes.h"
#include "sleep.h"
#include <TimerOne.h>


class Robot
{
    public: 
        Robot();

        void runController();

        void runMotors();

        void setReference(State _reference);

        State getReference();

        void setState(State _state);

        State getState();

        void setSleep(const bool& enable);

    private:
        State state, reference;

        IMU imu;

        MotorController leftMotor, rightMotor;

        Controller controller;

        Sleep sleep;

        ControlOutput controlOutput;
};


#endif