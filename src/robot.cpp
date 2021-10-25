#include "robot.h"
#include "Drivers/imu.h"
#include "Drivers/motorController.h"
#include "Controller.h"
#include "Drivers/sleep.h"
#include <TimerOne.h>



Robot::Robot()
{
    leftMotor = MotorController(LEFT_DRIVER_STP, LEFT_DRIVER_DIR, MAX_SPEED, MAX_ACCELERATION, LEFT_MOTOR_DIR, LEFT_DRIVER_MICROSTEPS);
    rightMotor = MotorController(RIGHT_DRIVER_STP, RIGHT_DRIVER_DIR, MAX_SPEED, MAX_ACCELERATION, RIGHT_MOTOR_DIR, RIGHT_DRIVER_MICROSTEPS);
    State state, reference; 
    Controller controller;
    IMU imu;
}

void Robot::runController()
{
    // automatic startup/shutdown 
    sleep.detectStartUp(state);

    imu.readData();

    state = imu.updateState(controlOutput, state.sleep);

    if (!state.sleep)
    {
        controlOutput = controller.calculateControlOutput(state, reference);

        // apply control
        leftMotor.setSpeed(controlOutput.leftSpeed);
        rightMotor.setSpeed(controlOutput.rightSpeed);
    }
}

void Robot::runMotors()
{
    this->leftMotor.run();
    this->rightMotor.run();
}

void Robot::setReference(State _reference)
{
    this->reference = _reference;
}

State Robot::getReference()
{
    return this->reference;
}

void Robot::setState(State _state)
{
    this->state = _state;
}

State Robot::getState()
{
    return this->state;
}

void Robot::setSleep(const bool& enable)
{
    if (enable)
        this->sleep.enableMotors();
    else 
        this->sleep.disableMotors();
}