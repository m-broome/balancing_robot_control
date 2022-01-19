#ifndef DATATYPES_H
#define DATATYPES_H

#include <I2Cdev.h>


struct ImuData
{
    int16_t accX{0};
    int16_t accY{0};
    int16_t accZ{0};
    int16_t gyroX{0};
    int16_t gyroY{0};
    int16_t gyroZ{0};
};

struct State
{
    // Control type     
    bool positionControl{true};
    bool speedControl{false};
    bool balanceControl{false};

    // Sleep
    bool sleep{false};

    // Control States
    float x{0};
    float ry{0};
    float rz{0};
    float velX{0};
    float velrz{0};
};

struct ControlOutput
{
    float leftSpeed{};
    float rightSpeed{};
};

#endif