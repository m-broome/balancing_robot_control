#include "mahonyFilter.h"
#include "config.h"
#include <cmath>
#include "dataTypes.h"
#include <MahonyAHRS.h>

MahonyFilter::MahonyFilter(){
}

State& MahonyFilter::mahonyFilterLib(ImuData imuData){
    filter.updateIMU(imuData.gyroX * GYRO_TO_RADS_PER_SECOND, imuData.gyroY * GYRO_TO_RADS_PER_SECOND, imuData.gyroZ * GYRO_TO_RADS_PER_SECOND, imuData.accX, imuData.accY, imuData.accZ);

    float roll = filter.getRoll() * RADS_TO_DEGREES;
    float pitch = filter.getPitch() * RADS_TO_DEGREES;
    float yaw = filter.getYaw() * RADS_TO_DEGREES;

    this->state.rx = pitch;
    this->state.ry = -roll;
    this->state.rz = yaw;
    
    return this->state;
}

void MahonyFilter::printQuaternion(Quaternion quaternion){
    Serial.print("W:"); Serial.print(quaternion.q0); Serial.print("\t");
    Serial.print("X:"); Serial.print(quaternion.q1); Serial.print("\t");
    Serial.print("Y:"); Serial.print(quaternion.q2); Serial.print("\t");
    Serial.print("Z:"); Serial.print(quaternion.q3); Serial.print("\n");
}

void MahonyFilter::printVector(vect3 vector){
    Serial.print("X:"); Serial.print(vector.v1); Serial.print("\t");
    Serial.print("Y:"); Serial.print(vector.v2); Serial.print("\t");
    Serial.print("Z:"); Serial.print(vector.v3); Serial.print("\n");
}

