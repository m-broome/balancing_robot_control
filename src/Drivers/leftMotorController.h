#ifndef LEFTMOTORCONTROLLER_H
#define LEFTMOTORCONTROLLER_H

# include <AccelStepper.h>
# include "../config.h"
# include "baseMotorController.h"
# include "../baseController.h"

class LeftMotorController : public BaseMotorController {

    public:
        LeftMotorController();
        void initialiseController();
        void applyControl(ControlOutput controlOutput);
};

#endif