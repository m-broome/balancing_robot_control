#include "controller.h"
#include "config.h"
#include "dataTypes.h"


ControlOutput Controller::calculateControlOutput(State& state, const State& reference)
{
    // update control type
    state.speedControl = reference.speedControl;
    state.positionControl = reference.positionControl;
    state.balanceControl = reference.balanceControl;

    /* ERROR TERMS  */
    // linear speed control
    float speedRyReference{this->calculatelinearSpeedTerm(state.velX, reference.velX)};

    // linear position control
    float positionRyReference{this->calculatelinearPositionTerm(state.x, reference.x)};

    // balance control
    float refRy = state.balanceControl ? reference.ry : state.speedControl ? speedRyReference : state.positionControl ? positionRyReference : positionRyReference;
    float u_linear{this->calculateBalanceTerm(state.ry, refRy)};

    // angular speed control
    float u_velrz{this->calculateAngularSpeedTerm(state.velrz, reference.velrz)};

    // angular position control
    float u_rz{this->calculateAngularPositionTerm(state.rz, reference.rz)};

    // angular reference
    float u_angular{reference.speedControl ? u_velrz : reference.positionControl ? u_rz : u_velrz};

    // Superposition of controls
    return (ControlOutput){-(u_linear + u_angular / 2), -(u_linear - u_angular / 2)};
}

float Controller::calculatelinearSpeedTerm(float stateVelX, float refVelX){
    float velXError{refVelX - stateVelX};
    float velXErrorGrad{-(stateVelX - this->velXPrev) / this->dt};
    this->velXPrev = stateVelX;
    this->velXErrorInt += velXError * this->dt;
    this->velXErrorInt = constrain(this->velXErrorInt, -SPEED_WINDUP_THRESHOLD, SPEED_WINDUP_THRESHOLD);
    float speedRyReference{PID_K_VX *velXError + PID_KD_VX * velXErrorGrad + PID_KI_VX * this->velXErrorInt};
    return speedRyReference;
}

float Controller::calculatelinearPositionTerm(float stateX, float refX){
    float xError{refX - stateX};
    float xErrorGrad{-(stateX - this->xPrev) / this->dt};
    this->xPrev = stateX;
    this->xErrorInt += xError * this->dt;
    this->xErrorInt = constrain(this->xErrorInt, -POSITION_WINDUP_THRESHOLD, POSITION_WINDUP_THRESHOLD);
    float positionRyReference{PID_K_X * xError + PID_KD_X * xErrorGrad + PID_KI_X * this->xErrorInt};
    return positionRyReference;
}

float Controller::calculateBalanceTerm(float stateRy, float refRy){
    float constrainedRefRy{constrain(refRy, -MAX_TILT_ANGLE, MAX_TILT_ANGLE)};
    float ryError{constrainedRefRy - stateRy};
    float ryErrorGrad{-(stateRy - this->ryPrev) / this->dt};
    this->ryPrev = stateRy;
    this->ryErrorInt += ryError * this->dt;
    this->ryErrorInt = constrain(this->ryErrorInt, -BALANCE_WINDUP_THRESHOLD, BALANCE_WINDUP_THRESHOLD);
    float u_linear{PID_K_RY * ryError + PID_KD_RY * ryErrorGrad + PID_KI_RY * this->ryErrorInt};
    return u_linear;
}

// open loop
float Controller::calculateAngularSpeedTerm(float stateVelRz, float refVelRz){
    return refVelRz;
}

// bang bang
float Controller::calculateAngularPositionTerm(float stateRz, float refRz){
    float rzError{refRz - stateRz};
    float u_rz{abs(rzError) <= ANGULAR_POSITION_ERROR_THRESHOLD ? 0 : rzError > 0 ? -POSITION_VEL_RZ : POSITION_VEL_RZ};
    return u_rz;
}