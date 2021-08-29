#include <Arduino.h>
#include <TimeLib.h>

#include "Drivers/imu.h"
#include "Drivers/baseMotorController.h"
#include "pidController.h"
#include "Drivers/leftMotorController.h"
#include "Drivers/rightMotorController.h"
#include "timer.h"
#include "config.h"


IMU imu;
LeftMotorController leftMotor;
RightMotorController rightMotor;
float speed = 3000;
State reference;
State state;
PIDController controller;
ControlOutput controlOutput;
double dt;
Timer timer;

void setup() {
  imu = IMU();
  leftMotor = LeftMotorController();
  rightMotor = RightMotorController();
  reference = State();
  dt = 0;
  timer.start();
}

void loop() {
  // evaluate time elapsed
  timer.getElapsed(dt);
  if (dt >= 1000/LOOP_FREQUENCY)
  {
    timer.reset();
    // Serial.print("Loop Frequency:"); Serial.print(1000/dt); Serial.print("\n");

    // get imu data
    imu.readData();
    state = imu.updateState();
    imu.printState();

    // calculate control output
    controlOutput = controller.calculateControlOutput(state, reference);

    // apply control Input
    leftMotor.applyControl(controlOutput);
    rightMotor.applyControl(controlOutput);
  }
  // run motors 
  // leftMotor.run();
  // rightMotor.run();
}