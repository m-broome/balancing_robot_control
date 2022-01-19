#include "motorController.h"
# include <AccelStepper.h>


MotorController::MotorController(int _StpPin, int _DirPin, float _maxSpeed, float _maxAcceleration, int _motorDir, int _microsteps) : 
maxSpeed(_maxSpeed), maxAcceleration(_maxAcceleration), motorDir(_motorDir), microsteps(_microsteps)
{
    pinMode(_StpPin, OUTPUT);
	pinMode(_DirPin, OUTPUT);

    this->motor = AccelStepper(1, _StpPin, _DirPin);

    motor.setMaxSpeed(maxSpeed);
	motor.setAcceleration(maxAcceleration);

    this->motorDir = motorDir;
    this->microsteps = microsteps;
}

MotorController::MotorController()
{}

void MotorController::setSpeed(const float& speed)
{
    this->motor.setSpeed(this->motorDir * this->microsteps * speed);
}

void MotorController::run()
{
    this->motor.runSpeed();
}