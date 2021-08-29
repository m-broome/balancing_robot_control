# include <AccelStepper.h>
# include "../config.h"
# include "rightMotorController.h"


RightMotorController::RightMotorController(){
    this->initialiseController();
}

void RightMotorController::initialiseController(){
    Serial.begin(38400);
    pinMode(RIGHT_DRIVER_STP, OUTPUT);
	pinMode(RIGHT_DRIVER_DIR, OUTPUT);
    pinMode(DRIVER_SLEEP, OUTPUT);
    digitalWrite(DRIVER_SLEEP, HIGH);
    this->motor = AccelStepper(1, RIGHT_DRIVER_STP, RIGHT_DRIVER_DIR);
    motor.setMaxSpeed(MAX_SPEED);
	motor.setAcceleration(MAX_ACCELERATION);
    this->motorDir = RIGHT_MOTOR_DIR;
}

void RightMotorController::applyControl(ControlOutput controlOutput){
    this->setSpeed((float)controlOutput.rightSpeed);
}


