#include "pidController.h"
#include "config.h"
#include "baseController.h"


ControlOutput PIDController::calculateControlOutput(State _state, State _reference){
    // Error Terms
    double ryError = _reference.ry - _state.ry;
    double ryErrorGrad = -(_state.ry - this->ryPrev) / this->dt;
    this->ryErrorInt += ryError * this->dt;
    this->ryErrorInt = this->limitIntegralWindup(this->ryErrorInt);

    // Evaluate control outputs
    double u_ry = PID_K_RY * (ryError + PID_KD_RY * ryErrorGrad + PID_KI_RY * this->ryErrorInt);
    double u_velrz = 0;

    // Superposition of controls
    return (ControlOutput){-(u_ry + u_velrz), -(u_ry - u_velrz)};
}

double PIDController::limitIntegralWindup(double integralTerm){
    if (abs(integralTerm) >= WINDUP_THRESHOLD){
        integralTerm = (integralTerm >= 0) ? WINDUP_THRESHOLD : -1 * WINDUP_THRESHOLD;
    }
    return integralTerm;
}