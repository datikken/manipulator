#include <Arduino.h>
#include "Joystick/Joystick.h"
#include "Axis/Axis.h"

Joystick joystick;
Axis axis;

void servoLoop() {
  axis.setMaxLeft();
  delay(1000);
  axis.setMaxRight();
}

void setup() {
  joystick.activateBtn();
  Serial.begin(9600);
  axis.setPin(9);
}

void loop() {
  joystick.debugPotentiomter();
  // servoLoop();
  delay(500); 
}
