#ifndef DATATYPES_H
#define DATATYPES_H

#include <I2Cdev.h>


struct ImuData
{
    int16_t accX = 0;
    int16_t accY = 0;
    int16_t accZ = 0;
    int16_t gyroX = 0;
    int16_t gyroY = 0;
    int16_t gyroZ = 0;
};

struct State
{
    double x = 0;
    double y = 0;
    double z = 0;
    double rx = 0;
    double ry = 0;
    double rz = 0;
    double velX = 0;
    double velY = 0;
    double velZ = 0;
    double velrx = 0;
    double velry = 0;
    double velrz = 0;
    double accX = 0;
    double accY = 0;
    double accZ = 0;
    double accrx = 0;
    double accry = 0;
    double accrz = 0;
};

struct Quaternion
{
    double q0 = 1;
    double q1 = 0;
    double q2 = 0;
    double q3 = 1;
};

struct EulerAngles {
    double roll, pitch, yaw;
};

struct vect3
{
    double v1 = 0;
    double v2 = 0;
    double v3 = 0;
};


#endif