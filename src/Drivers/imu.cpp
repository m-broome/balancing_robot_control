#include "imu.h"
#include "../config.h"
#include <I2Cdev.h>
#include <MPU6050.h>


IMU::IMU(){
    Serial.begin(115200);
    this->initializeImu();
}

void IMU::initializeImu(){
    Wire.begin();
    this->imu.initialize();

    // Set Imu Offsets
    this->imu.setXAccelOffset(ACCEL_OFFSET_X);
    this->imu.setYAccelOffset(ACCEL_OFFSET_Y);
    this->imu.setZAccelOffset(ACCEL_OFFSET_Z);
    this->imu.setXGyroOffset(GYRO_OFFSET_RX);
    this->imu.setYGyroOffset(GYRO_OFFSET_RY);
    this->imu.setZGyroOffset(GYRO_OFFSET_RZ);
}

ImuData& IMU::readData(){
    imu.getMotion6(&this->imuData.accX,  &this->imuData.accY,  &this->imuData.accZ,  &this->imuData.gyroX, &this->imuData.gyroY, &this->imuData.gyroZ);
    return this->imuData;
}

State& IMU::updateState(){
    this->state = this->mahonyFilter.mahonyFilter(this->imuData); 

    //TODO CONVERT FROM GLOBAL BACK TO LOCAL COORDINATE SYSTEM
    return this->state;
}

void IMU::printData(){
    Serial.print("Raw accX:"); Serial.print(this->imuData.accX); Serial.print("\t");
    Serial.print("Raw accY:"); Serial.print(this->imuData.accY); Serial.print("\t");
    Serial.print("Raw accZ:"); Serial.print(this->imuData.accZ); Serial.print("\t");
    Serial.print("Raw angVelX:"); Serial.print(this->imuData.gyroX); Serial.print("\t");
    Serial.print("Raw angVelY:"); Serial.print(this->imuData.gyroY); Serial.print("\t");
    Serial.print("Raw angVelZ:"); Serial.println(this->imuData.gyroZ);
}

void IMU::printState(){
    // Serial.print("X:"); Serial.print(this->state.x); Serial.print("\t");
    // Serial.print("Y:"); Serial.print(this->state.y); Serial.print("\t");
    // Serial.print("Z:"); Serial.print(this->state.z); Serial.print("\t");
    // Serial.print("RX:"); Serial.print(this->state.rx); Serial.print("\t");
    Serial.print("RY:"); Serial.print(this->state.ry); Serial.print("\n");
    Serial.print("RZ:"); Serial.print(this->state.rz); Serial.print("\n");
    // Serial.print("VX:"); Serial.print(this->state.velX); Serial.print("\t");
    // Serial.print("VY:"); Serial.print(this->state.velY); Serial.print("\t");
    // Serial.print("VZ:"); Serial.print(this->state.velZ); Serial.print("\t");
    // Serial.print("VRX:"); Serial.print(this->state.velrx); Serial.print("\t");
    // Serial.print("VRY:"); Serial.print(this->state.velry); Serial.print("\t");
    // Serial.print("VRZ:"); Serial.print(this->state.velrz); Serial.print("\t");
    // Serial.print("AX:"); Serial.print(this->state.accX); Serial.print("\t");
    // Serial.print("AY:"); Serial.print(this->state.accY); Serial.print("\t");
    // Serial.print("AZ:"); Serial.print(this->state.accZ); Serial.print("\t");
    // Serial.print("ARX:"); Serial.print(this->state.accrx); Serial.print("\t");
    // Serial.print("ARY:"); Serial.print(this->state.accry); Serial.print("\t");
    // Serial.print("ARZ:"); Serial.println(this->state.accrz);
}
