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
    if (imu.getIntDataReadyStatus()){
        imu.getMotion6(&this->imuData.accX,  &this->imuData.accY,  &this->imuData.accZ,  &this->imuData.gyroX, &this->imuData.gyroY, &this->imuData.gyroZ);
    }
    return this->imuData;
}

State& IMU::updateState(){
    // this->state = this->mahonyFilter(this->imuData); 
    this->state = this->complementaryFilter(this->imuData); 

    return this->state;
}

// Based implementation by jjrobots: https://github.com/jjrobots/B-ROBOT_EVO2/blob/master/Arduino/BROBOT_EVO2/MPU6050.ino
State& IMU::complementaryFilter(ImuData imuData)
{
  float accel_angle = -atan2f((float)imuData.accX, (float)imuData.accZ) * RADS_TO_DEGREES;
  float gyro_value = (imuData.gyroY - this->gyro_offset) * GYRO_TO_DEGREES_PER_SECOND;

  // Complementary filter
  // We integrate the gyro rate value to obtain the angle in the short term and we take the accelerometer angle with a low pass filter in the long term...
  this->state.ry = GYRO_WEIGHTING * (this->state.ry + gyro_value * dt) + ACCELEROMETER_WEIGHTING * accel_angle;

  // Gyro bias correction
  // We supose that the long term mean of the gyro_value should tend to zero (gyro_offset). This means that the robot is not continuosly rotating.
  int16_t correction = constrain(imuData.gyroY, this->gyro_offset - GYRO_CORRECTION_LIMIT, this->gyro_offset + GYRO_CORRECTION_LIMIT); // limit corrections...
  this->gyro_offset = this->gyro_offset * GYRO_OFFSET_WEIGHTING + correction * GYRO_OFFSET_CORRECTION_WEIGHTING; // Time constant of this correction is around 20 sec.

  return this->state;
}

State& IMU::mahonyFilter(ImuData imuData){
    filter.updateIMU(imuData.gyroX * GYRO_TO_RADS_PER_SECOND, imuData.gyroY * GYRO_TO_RADS_PER_SECOND, imuData.gyroZ * GYRO_TO_RADS_PER_SECOND, imuData.accX, imuData.accY, imuData.accZ);

    float roll = filter.getRoll();
    float pitch = filter.getPitch();
    float yaw = filter.getYaw();

    this->state.rx = pitch * RADS_TO_DEGREES;
    this->state.ry = -roll * RADS_TO_DEGREES;
    this->state.rz = yaw * RADS_TO_DEGREES;
    
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
    // Serial.print("RZ:"); Serial.print(this->state.rz); Serial.print("\n");
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
