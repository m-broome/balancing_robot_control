#include "imu.h"
#include "../config.h"
#include <I2Cdev.h>
#include <MPU6050.h>


IMU::IMU()
{
    Serial.begin(115200);

    this->initializeImu();
}

void IMU::initializeImu()
{
    Wire.begin();

    this->imu.initialize();

    // Set Imu Offsets
    this->imu.setXAccelOffset(ACCEL_OFFSET_X);
    this->imu.setYAccelOffset(ACCEL_OFFSET_Y);
    this->imu.setZAccelOffset(ACCEL_OFFSET_Z);
    this->imu.setXGyroOffset(GYRO_OFFSET_RX);
    this->imu.setYGyroOffset(GYRO_OFFSET_RY);
    this->imu.setZGyroOffset(GYRO_OFFSET_RZ);

    // Allow Imu to reach steady state
    ControlOutput controlOutput = (ControlOutput){0, 0};

    for(int i{0}; i <= IMU_INITIALISATION_ITERATIONS; ++i){

        if (this->readData())
        {
            this->updateState(controlOutput, false);
        } 
    }
}

bool IMU::readData()
{
    if (imu.getIntDataReadyStatus())
    {
        imu.getMotion6(&this->imuData.accX,  &this->imuData.accY,  &this->imuData.accZ,  &this->imuData.gyroX, &this->imuData.gyroY, &this->imuData.gyroZ);

        return true;
    }
    return false;
}

State& IMU::updateState(const ControlOutput& controlOutput,const bool& motorsDisabled)
{
    this->state.ry = this->complementaryFilter(this->imuData); 

    if (!motorsDisabled)
    {
        this->state.velX = (controlOutput.leftSpeed * LEFT_STEPS_PER_SECOND_TO_METRES_PER_SECOND + controlOutput.rightSpeed * RIGHT_STEPS_PER_SECOND_TO_METRES_PER_SECOND) / 2;

        this->state.velrz = (controlOutput.leftSpeed * LEFT_STEPS_PER_SECOND_TO_METRES_PER_SECOND - controlOutput.rightSpeed * RIGHT_STEPS_PER_SECOND_TO_METRES_PER_SECOND) * (RADS_TO_DEGREES/ROBOT_RADIUS_METERS);
        
        this->state.x += this->state.velX * LOOP_PERIOD;
        
        this->state.rz += this->state.velrz * LOOP_PERIOD;
    }
    return this->state;
}

// Based implementation by jjrobots: https://github.com/jjrobots/B-ROBOT_EVO2/blob/master/Arduino/BROBOT_EVO2/MPU6050.ino
float IMU::complementaryFilter(const ImuData& imuData)
{
    float accel_angle{-atan2f((float)imuData.accX, (float)imuData.accZ) * RADS_TO_DEGREES};

    float gyro_value{(imuData.gyroY - this->gyro_offset) * GYRO_TO_DEGREES_PER_SECOND};

    // Complementary filter
    // We integrate the gyro rate value to obtain the angle in the short term and we take the accelerometer angle with a low pass filter in the long term...
    float ry{GYRO_WEIGHTING * (this->state.ry + gyro_value * LOOP_PERIOD) + ACCELEROMETER_WEIGHTING * accel_angle};
    
    // Gyro bias correction
    // We supose that the long term mean of the gyro_value should tend to zero (gyro_offset). This means that the robot is not continuosly rotating.
    int16_t correction{constrain(imuData.gyroY, this->gyro_offset - GYRO_CORRECTION_LIMIT, this->gyro_offset + GYRO_CORRECTION_LIMIT)}; // limit corrections...

    this->gyro_offset = this->gyro_offset * GYRO_OFFSET_WEIGHTING + correction * GYRO_OFFSET_CORRECTION_WEIGHTING; // Time constant of this correction is around 20 sec.

    return ry;
}

void IMU::printData()
{
    Serial.print("Raw accX:"); Serial.print(this->imuData.accX); Serial.print("\t");
    Serial.print("Raw accY:"); Serial.print(this->imuData.accY); Serial.print("\t");
    Serial.print("Raw accZ:"); Serial.print(this->imuData.accZ); Serial.print("\t");
    Serial.print("Raw angVelX:"); Serial.print(this->imuData.gyroX); Serial.print("\t");
    Serial.print("Raw angVelY:"); Serial.print(this->imuData.gyroY); Serial.print("\t");
    Serial.print("Raw angVelZ:"); Serial.print(this->imuData.gyroZ); Serial.print("\n");
}

void IMU::printState()
{
    Serial.print("X:"); Serial.print(this->state.x); Serial.print("\t");
    Serial.print("RY:"); Serial.print(this->state.ry); Serial.print("\t");
    Serial.print("RZ:"); Serial.print(this->state.rz); Serial.print("\t");
    Serial.print("VX:"); Serial.print(this->state.velX); Serial.print("\t");
    Serial.print("VRZ:"); Serial.print(this->state.velrz); Serial.print("\n");
}
