#pragma once


//===========================================================================
//============================= Pins ========================================
//===========================================================================

//IMU: MPU-6050
#define IMU_SCL 19
#define IMU_SDA 18
#define IMU_INT 17

//Stepper motor Drivers : A4988
#define DRIVER_SLEEP 5
#define RIGHT_DRIVER_STP 6
#define RIGHT_DRIVER_DIR 2
#define LEFT_DRIVER_STP 4
#define LEFT_DRIVER_DIR 3


//===========================================================================
//============================= Motors ======================================
//===========================================================================

#define MAX_ACCELERATION 100000
#define MAX_SPEED 10000

#define LEFT_MOTOR_DIR -1
#define RIGHT_MOTOR_DIR 1

#define LEFT_DRIVER_MICROSTEPS 16
#define RIGHT_DRIVER_MICROSTEPS 16


//===========================================================================
//============================= IMU =========================================
//===========================================================================

// Sensitivities
# define GYRO_SENSITIVITY 250 // degrees/second
# define ACCEL_SENSITIVITY 2 // g
# define OUTPUT_SCALE 32767.5 //(int16 represents full scale)

// Unit Conversions
# define RADS_TO_DEGREES 180/3.1415
# define DEGREES_TO_RADS 3.1415/180

# define G_TO_MS2 9.81
# define MS2_TO_G 1/9.81

# define ACCEL_TO_G ACCEL_SENSITIVITY / OUTPUT_SCALE
# define ACCEL_TO_METERS_PER_SECOND_SQUARED ACCEL_TO_G * G_TO_MS2

# define GYRO_TO_DEGREES_PER_SECOND GYRO_SENSITIVITY / OUTPUT_SCALE
# define GYRO_TO_RADS_PER_SECOND GYRO_TO_DEGREES_PER_SECOND * DEGREES_TO_RADS

// Accelerometer Offsets
# define ACCEL_OFFSET_X -40
# define ACCEL_OFFSET_Y 1087 
# define ACCEL_OFFSET_Z 1415

// Gyro Offsets
# define GYRO_OFFSET_RX 21 
# define GYRO_OFFSET_RY 3 
# define GYRO_OFFSET_RZ -26

// Complementary Filter 
# define GYRO_WEIGHTING 0.99
# define ACCELEROMETER_WEIGHTING 0.01

# define GYRO_CORRECTION_LIMIT 10
# define GYRO_OFFSET_WEIGHTING 0.9995
# define GYRO_OFFSET_CORRECTION_WEIGHTING 0.0005


//===========================================================================
//============================= Controller ==================================
//===========================================================================

// Control Loop Timing
# define LOOP_FREQUENCY 100.0
# define WATCHDOG_THRESHOLD 300

// PID Controller
# define WINDUP_THRESHOLD 6000

# define PID_K_RY 14.0
# define PID_KD_RY 5.0
# define PID_KI_RY 0.0


//===========================================================================
//============================= Motion Constraints ==========================
//===========================================================================

// Switch on and switch off
# define SWITCH_ON_ANGLE_DEGREES 5
# define SWITCH_OFF_ANGLE_DEGREES 60