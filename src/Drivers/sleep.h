#ifndef SLEEP_H
#define SLEEP_H

# include "dataTypes.h"


class Sleep
{
    private:
        bool motorsDisabled;

    public:
        Sleep();

        void disableMotors();

        void enableMotors();

        void detectStartUp(State& state);
};

# endif