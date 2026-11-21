#include <Arduino.h>
#include <Servo.h>
#include "Axis.h"

void Axis::setPin(int pin) { 
    pinMode(pin, OUTPUT);
    servo.attach(pin); 
};

void Axis::setMaxLeft() { 
    for (pos = kMin; pos <= kMax; pos += 1) {
        servo.write(pos);             
        delay(kDefaultStepDelayMs);
    }
}
void Axis::setMaxRight() { 
    for (pos = kMax; pos >= kMin; pos -= 1) { // goes from 180 degrees to 0 degrees
        servo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(kDefaultStepDelayMs);              // waits 15ms for the servo to reach the position
    }
}

void Axis::rotateClockwise(uint16_t stepDelayMs) {
    if (pos >= kMax) return;          // already at upper limit, nothing to do
    pos += kStep;
    servo.write(pos);
    delay(stepDelayMs);               // let the servo physically reach this step
}

void Axis::rotateCounterClockwise(uint16_t stepDelayMs) {
    if (pos <= kMin) return;          // already at lower limit, nothing to do
    pos -= kStep;
    servo.write(pos);
    delay(stepDelayMs);
}

