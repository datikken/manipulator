#pragma once

#include <Arduino.h>
#include <Servo.h>

class Axis {
    Servo servo;
    int pos = 0;
    public:
        void setPin(int pin);
        void setMaxLeft();
        void setMaxRight();
};