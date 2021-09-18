#ifndef IMU_H
#define IMU_H

#include <I2Cdev.h>
#include <MPU6050.h>
#include <MahonyAHRS.h>

#include "Wire.h"
#include "timer.h"
#include "dataTypes.h"
#include "config.h"


class IMU {
    private:
        float dt = 1/LOOP_FREQUENCY;
        float gyro_offset = 0;

        MPU6050 imu;
        ImuData imuData;
        Mahony filter;
        State state;

        void initializeImu();
        State& mahonyFilter(ImuData imuData);
        float complementaryFilter(ImuData imuData);
        
    public:
        IMU();
        bool readData();
        State& updateState(ControlOutput controlOutput);
        void printData();
        void printState();
};

#endif