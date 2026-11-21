#include <Arduino.h>
#include "Joystick/Joystick.h"
#include "Axis/Axis.h"
#include "AxisManipulator/AxisManipulator.h"

Joystick joystick;
Axis axis;
AxisManipulator manipulator(axis);   // joystick center ~512, dead zone +/-30

void setup() {
  joystick.activateBtn();
  Serial.begin(9600);
  axis.setPin(9);
}

void loop() {
  // one servo step per pass in the joystick's X direction
  manipulator.update(joystick.getValX());
}

