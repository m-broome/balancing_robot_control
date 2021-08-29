#include "mahonyFilter.h"
#include "config.h"
#include <cmath>
#include "dataTypes.h"
#include <MahonyAHRS.h>

MahonyFilter::MahonyFilter(){
}

State& MahonyFilter::mahonyFilter(ImuData imuData){
    filter.updateIMU(imuData.gyroX * GYRO_TO_RADS_PER_SECOND, imuData.gyroY * GYRO_TO_RADS_PER_SECOND, imuData.gyroZ * GYRO_TO_RADS_PER_SECOND, imuData.accX, imuData.accY, imuData.accZ);

    float roll = filter.getRoll() * RADS_TO_DEGREES;
    float pitch = filter.getPitch() * RADS_TO_DEGREES;
    float yaw = filter.getYaw() * RADS_TO_DEGREES;

    this->state.rx = pitch;
    this->state.ry = -roll;
    this->state.rz = yaw;
    
    return this->state;
}

