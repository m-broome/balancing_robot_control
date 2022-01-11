#include "Controller.h"
#include "config.h"


ControlOutput Controller::calculateControlOutput(State& state, const State& reference)
{
    // update control type
    state.speedControl = reference.speedControl;
    state.positionControl = reference.positionControl;
    state.balanceControl = reference.balanceControl;

    /* ERROR TERMS  */
    // linear speed control
    float velXError{reference.velX - state.velX};
    float velXErrorGrad{-(state.velX - this->velXPrev) / this->dt};
    this->velXPrev = state.velX;
    this->velXErrorInt += velXError * this->dt;
    this->velXErrorInt = constrain(this->velXErrorInt, -SPEED_WINDUP_THRESHOLD, SPEED_WINDUP_THRESHOLD);
    float speedRyReference{PID_K_VX *velXError + PID_KD_VX * velXErrorGrad + PID_KI_VX * this->velXErrorInt};

    // linear position control
    float xError{reference.x - state.x};
    float xErrorGrad{-(state.x - this->xPrev) / this->dt};
    this->xPrev = state.x;
    this->xErrorInt += xError * this->dt;
    this->xErrorInt = constrain(this->xErrorInt, -POSITION_WINDUP_THRESHOLD, POSITION_WINDUP_THRESHOLD);
    float positionRyReference{PID_K_X * xError + PID_KD_X * xErrorGrad + PID_KI_X * this->xErrorInt};

    // balance control
    float refRy = state.balanceControl ? reference.ry : state.speedControl ? speedRyReference : state.positionControl ? positionRyReference : positionRyReference;
    float constrainedRefRy{constrain(refRy, -MAX_TILT_ANGLE, MAX_TILT_ANGLE)};
    float ryError{constrainedRefRy - state.ry};
    float ryErrorGrad{-(state.ry - this->ryPrev) / this->dt};
    this->ryPrev = state.ry;
    this->ryErrorInt += ryError * this->dt;
    this->ryErrorInt = constrain(this->ryErrorInt, -BALANCE_WINDUP_THRESHOLD, BALANCE_WINDUP_THRESHOLD);
    float u_linear{PID_K_RY * ryError + PID_KD_RY * ryErrorGrad + PID_KI_RY * this->ryErrorInt};

    // angular speed control (open loop)
    float u_velrz{reference.velrz};

    // angular position control (open loop)
    float rzError{reference.rz - state.rz};
    float u_rz{abs(rzError) <= ANGULAR_POSITION_ERROR_THRESHOLD ? 0 : rzError > 0 ? -POSITION_VEL_RZ : POSITION_VEL_RZ};
    float u_angular{reference.speedControl ? u_velrz : reference.positionControl ? u_rz : u_velrz};

    // Superposition of controls
    return (ControlOutput){-(u_linear + u_angular / 2), -(u_linear - u_angular / 2)};
}