#include <Arduino.h>
#include <TimeLib.h>

#include "Drivers/imu.h"
#include "Drivers/baseMotorController.h"
#include "pidController.h"
#include "Drivers/leftMotorController.h"
#include "Drivers/rightMotorController.h"
#include "timer.h"
#include "config.h"
#include "startup.h"


IMU imu;
LeftMotorController leftMotor;
RightMotorController rightMotor;
StartUp startUp;
State state, reference; 
PIDController controller;
ControlOutput controlOutput;
double dt;
Timer timer;

void setup() {
  imu = IMU();
  startUp = StartUp();
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

    // automatic startup/shutdown 
    startUp.detectStartUp(state);

    // calculate control output
    controlOutput = controller.calculateControlOutput(state, reference);

    // apply control Input
    leftMotor.applyControl(controlOutput);
    rightMotor.applyControl(controlOutput);
  }
  // run motors 
  leftMotor.run();
  rightMotor.run();
}