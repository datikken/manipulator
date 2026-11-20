#include <Arduino.h>
#include "Joystick/Joystick.h"

Joystick joystick;

void setup() {
  joystick.activateBtn();
  Serial.begin(9600);
}

void loop() {
  Serial.print("X:");
  Serial.print(joystick.getValX());

  Serial.print(" | Y:");
  Serial.print(joystick.getValY());

  Serial.print(" | Z: ");
  Serial.println(joystick.getValZ());

  delay(500); // пауза перед следующим считыванием данных
}
