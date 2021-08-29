#ifndef MAHONYFILTER_H
#define MAHONYFILTER_H

#include "dataTypes.h"
#include "timer.h"
#include <MahonyAHRS.h>


class MahonyFilter{
    private:
        State state;
        Mahony filter;

    public:
        MahonyFilter();
        State& mahonyFilterLib(ImuData imuData);
        void printQuaternion(Quaternion quaternion);  
        void printVector(vect3 vector);
};

#endif