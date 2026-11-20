#pragma once

#include <Arduino.h>
#include <Servo.h>

class Axis {
    Servo servo;
    public:
        void setPin(int pin);
        void setMaxLeft();
        void setMaxRight();
};