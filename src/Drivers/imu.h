#ifndef IMU_H
#define IMU_H

#include <I2Cdev.h>
#include <MPU6050.h>
#include "Wire.h"
#include "mahonyFilter.h"
#include "timer.h"
#include "dataTypes.h"
#include "config.h"


class IMU {
    private:
        double dt = 1/LOOP_FREQUENCY;

        MPU6050 imu;
        ImuData imuData;
        MahonyFilter mahonyFilter;
        State state;
        void initializeImu();
        
    public:
        IMU();
        ImuData& readData();
        State& updateState();
        void printData();
        void printState();
};

#endif