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
    float x = 0;
    float y = 0;
    float z = 0;
    float rx = 0;
    float ry = 0;
    float rz = 0;
    float velX = 0;
    float velY = 0;
    float velZ = 0;
    float velrx = 0;
    float velry = 0;
    float velrz = 0;
    float accX = 0;
    float accY = 0;
    float accZ = 0;
    float accrx = 0;
    float accry = 0;
    float accrz = 0;
};

struct ControlOutput
{
    float leftSpeed;
    float rightSpeed;
};

struct Quaternion
{
    float q0 = 1;
    float q1 = 0;
    float q2 = 0;
    float q3 = 1;
};

struct EulerAngles {
    float roll, pitch, yaw;
};

struct vect3
{
    float v1 = 0;
    float v2 = 0;
    float v3 = 0;
};


#endif