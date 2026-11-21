#include <Arduino.h>
#include <Servo.h>
#include "Axis.h"

void Axis::setPin(int pin) { 
    pinMode(pin, OUTPUT);
    servo.attach(pin); 
};

void Axis::setMaxLeft() { 
    for (pos = 0; pos <= 180; pos += 1) {
        servo.write(pos);             
        delay(15);                       
    }
}
void Axis::setMaxRight() { 
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        servo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
}
