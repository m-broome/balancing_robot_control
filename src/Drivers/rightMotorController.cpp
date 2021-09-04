# include <AccelStepper.h>
# include "../config.h"
# include "rightMotorController.h"


RightMotorController::RightMotorController(){
    this->initialiseController();
}

void RightMotorController::initialiseController(){
    pinMode(RIGHT_DRIVER_STP, OUTPUT);
	pinMode(RIGHT_DRIVER_DIR, OUTPUT);
    this->motor = AccelStepper(1, RIGHT_DRIVER_STP, RIGHT_DRIVER_DIR);
    motor.setMaxSpeed(MAX_SPEED);
	motor.setAcceleration(MAX_ACCELERATION);
    this->motorDir = RIGHT_MOTOR_DIR;
    this->microsteps = RIGHT_DRIVER_MICROSTEPS;
}

void RightMotorController::applyControl(ControlOutput controlOutput){
    this->setSpeed((float)controlOutput.rightSpeed);
}