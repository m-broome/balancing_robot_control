#include <Arduino.h>
#include <TimeLib.h>

#include "serialProxy.h"
#include "config.h"
#include "robot.h"


Robot robot;
SerialProxy serialProxy;

void runRobot()
{
  robot.runController();
}

void setup()
{
  Timer1.initialize(LOOP_PERIOD * 1e6);
  Timer1.attachInterrupt(runRobot);
}

void loop()
 {
  if (Serial.available())
  {
    serialProxy.executeCommand(robot);
  }

  robot.runMotors();
}