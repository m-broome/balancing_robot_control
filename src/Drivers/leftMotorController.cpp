# include <AccelStepper.h>
# include "../config.h"
# include "leftMotorController.h"
# include "../baseController.h"


LeftMotorController::LeftMotorController(){
    this->initialiseController();
}

void LeftMotorController::initialiseController(){
    pinMode(LEFT_DRIVER_STP, OUTPUT);
	pinMode(LEFT_DRIVER_DIR, OUTPUT);
    this->motor = AccelStepper(1, LEFT_DRIVER_STP, LEFT_DRIVER_DIR);
    motor.setMaxSpeed(MAX_SPEED);
	motor.setAcceleration(MAX_ACCELERATION);
    this->motorDir = LEFT_MOTOR_DIR;
}

void LeftMotorController::applyControl(ControlOutput controlOutput){
    this->setSpeed((float)controlOutput.leftSpeed);
}