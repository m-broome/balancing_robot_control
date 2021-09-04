#include "baseMotorController.h"
# include <AccelStepper.h>


void BaseMotorController::setSpeed(float speed){
    this->motor.setSpeed(this->motorDir * this->microsteps * speed);
}

void BaseMotorController::run(){
    this->motor.runSpeed();
}