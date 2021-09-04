#include "pidController.h"
#include "config.h"
#include "baseController.h"


ControlOutput PIDController::calculateControlOutput(State _state, State _reference){
    // Error Terms
    float ryError = _reference.ry - _state.ry;
    float ryErrorGrad = -(_state.ry - this->ryPrev) / this->dt;
    this->ryErrorInt += ryError * this->dt;
    this->ryErrorInt = constrain(this->ryErrorInt, -WINDUP_THRESHOLD, WINDUP_THRESHOLD);

    // Evaluate control outputs
    float u_ry = PID_K_RY * (ryError + PID_KD_RY * ryErrorGrad + PID_KI_RY * this->ryErrorInt);
    float u_velrz = 0;

    // Superposition of controls
    return (ControlOutput){-(u_ry + u_velrz), -(u_ry - u_velrz)};
}