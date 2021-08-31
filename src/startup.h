#ifndef StartUp_h
#define StartUp_h

# include "Drivers/leftMotorController.h"
# include "Drivers/rightMotorController.h"
# include "dataTypes.h"


class StartUp{
    private:
        bool motorsDisabled;

    public:
        StartUp();
        void detectStartUp(State state);
};

# endif