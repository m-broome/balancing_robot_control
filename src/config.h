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
//============================= Kinematics ==================================
//===========================================================================

#define WHEEL_RADIUS_METERS 0.045
#define ROBOT_RADIUS_METERS 0.13



//===========================================================================
//============================= Motion Constraints =======================
//===========================================================================

// Switch on and switch off
# define SWITCH_ON_ANGLE_DEGREES 3
# define SWITCH_OFF_ANGLE_DEGREES 40


//===========================================================================
//============================= Motors ======================================
//===========================================================================

#define MAX_ACCELERATION 100000
#define MAX_SPEED 10000

#define LEFT_MOTOR_DIR -1
#define RIGHT_MOTOR_DIR 1

#define LEFT_DRIVER_MICROSTEPS 16
#define RIGHT_DRIVER_MICROSTEPS 16

#define LEFT_MOTOR_STEP_ANGLE_DEGREES 1.8
#define RIGHT_MOTOR_STEP_ANGLE_DEGREES 1.8

// Unit Conversions
# define RADS_TO_DEGREES 180/3.1415
# define DEGREES_TO_RADS 3.1415/180

#define LEFT_MOTOR_STEP_ANGLE_RADS LEFT_MOTOR_STEP_ANGLE_DEGREES * DEGREES_TO_RADS
#define RIGHT_MOTOR_STEP_ANGLE_RADS RIGHT_MOTOR_STEP_ANGLE_DEGREES * DEGREES_TO_RADS

# define LEFT_STEPS_PER_SECOND_TO_METRES_PER_SECOND  LEFT_MOTOR_STEP_ANGLE_DEGREES * DEGREES_TO_RADS * WHEEL_RADIUS_METERS
# define RIGHT_STEPS_PER_SECOND_TO_METRES_PER_SECOND  RIGHT_MOTOR_STEP_ANGLE_DEGREES * DEGREES_TO_RADS * WHEEL_RADIUS_METERS


//===========================================================================
//============================= IMU =========================================
//===========================================================================

// Initialisation
# define IMU_INITIALISATION_ITERATIONS 100

// Sensitivities
# define GYRO_SENSITIVITY 250 // degrees/second
# define ACCEL_SENSITIVITY 2 // g
# define OUTPUT_SCALE 32767.5 //(int16 represents full scale)

// Unit Conversions
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
// Balance Control
# define PID_K_RY 35.0
# define PID_KD_RY 0.8
# define PID_KI_RY 0.004
# define BALANCE_WINDUP_THRESHOLD 6000

// Speed Control
# define PID_K_VX 7.0
# define PID_KD_VX 0.006
# define PID_KI_VX 0.0015
# define SPEED_WINDUP_THRESHOLD 600

// Position Control
# define PID_K_X 30.0
# define PID_KD_X 0.0
# define PID_KI_X 0.0
# define POSITION_WINDUP_THRESHOLD 300

// Rotation Control
# define POSITION_VEL_RZ 90
# define ANGULAR_POSITION_ERROR_THRESHOLD 1


//===========================================================================
//============================= Serial Communication ========================
//===========================================================================

// Serial frequency
# define SERIAL_BAUD_RATE 9600

// Json parameters 
# define JSON_DOCUMENT_SIZE 512

