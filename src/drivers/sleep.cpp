# include "sleep.h"
# include <AccelStepper.h>
# include "dataTypes.h"
# include "config.h"

Sleep::Sleep()
{
    pinMode(DRIVER_SLEEP, OUTPUT);

    digitalWrite(DRIVER_SLEEP, LOW);

    this->motorsDisabled = true;
}

void Sleep::enableMotors()
{
    digitalWrite(DRIVER_SLEEP, HIGH);

    this->motorsDisabled = false;
}

void Sleep::disableMotors()
{
    digitalWrite(DRIVER_SLEEP, LOW);

    this->motorsDisabled = true;
}

void Sleep::detectStartUp(State& state)
{
    if (abs(state.ry) <= SWITCH_ON_ANGLE_DEGREES && this->motorsDisabled){

        this->enableMotors();
    }
    else if (abs(state.ry) >= SWITCH_OFF_ANGLE_DEGREES && !this->motorsDisabled){

        this->disableMotors();
    }
    state.sleep = this->motorsDisabled;
}