#include "Axis.h"

void Axis::setPin(int pin) { servo.attach(pin); };
void Axis::setMaxLeft() { servo.write(0); }
void Axis::setMaxRight() { servo.write(180); }
