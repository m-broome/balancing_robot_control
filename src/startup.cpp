# include "startup.h"

# include <AccelStepper.h>

# include "Drivers/leftMotorController.h"
# include "Drivers/rightMotorController.h"
# include "dataTypes.h"
# include "config.h"

StartUp::StartUp(){
    pinMode(DRIVER_SLEEP, OUTPUT);
    digitalWrite(DRIVER_SLEEP, LOW);
    this->motorsDisabled = true;
}

void StartUp::detectStartUp(State state){
    if (abs(state.ry) <= SWITCH_ON_ANGLE_DEGREES && this->motorsDisabled){
        digitalWrite(DRIVER_SLEEP, HIGH);
        this->motorsDisabled = false;
    }
    else if (abs(state.ry) >= SWITCH_OFF_ANGLE_DEGREES && !this->motorsDisabled){
        digitalWrite(DRIVER_SLEEP, LOW);
        this->motorsDisabled = true;
    }
}