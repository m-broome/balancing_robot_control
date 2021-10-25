#ifndef IMU_H
#define IMU_H

#include <I2Cdev.h>
#include <MPU6050.h>
#include <MahonyAHRS.h>

#include "Wire.h"
#include "dataTypes.h"
#include "config.h"


class IMU
{
    public:
        IMU();
        
        bool readData();

        State& updateState(const ControlOutput& controlOutput, const bool& motorsEnabled);

        void printData();

        void printState();

    private:
        float gyro_offset = 0;

        MPU6050 imu;

        ImuData imuData;

        Mahony filter;

        State state;

        void initializeImu();

        float complementaryFilter(const ImuData& imuData);
};

#endif