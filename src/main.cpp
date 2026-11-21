#include <Arduino.h>
#include "Joystick/Joystick.h"
#include "Axis/Axis.h"
#include "AxisManipulator/AxisManipulator.h"

constexpr uint8_t kPinServoX = 9;
constexpr uint8_t kPinServoY = 8;

Joystick joystick;
Axis axisX;
Axis axisY;
AxisManipulator manipulatorX(axisX);   // joystick center ~512, dead zone +/-30
AxisManipulator manipulatorY(axisY);

void setup() {
  Serial.begin(9600);
  joystick.activateBtn();
  axisX.setPin(kPinServoX);
  axisY.setPin(kPinServoY);
}

void loop() {
  // one servo step per pass, X servo on pin 9, Y servo on pin 8
  manipulatorX.update(joystick.getValX());
  manipulatorY.update(joystick.getValY());
}

