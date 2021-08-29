#ifndef RIGHTMOTORCONTROLLER_H
#define RIGHTMOTORCONTROLLER_H

# include <AccelStepper.h>
# include "../config.h"
# include "baseMotorController.h"
# include "../baseController.h"

class RightMotorController : public BaseMotorController {

    public:
        RightMotorController();
        void initialiseController();
        void applyControl(ControlOutput controlOutput);
};

#endif