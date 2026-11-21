#pragma once

#include <Arduino.h>
#include <Servo.h>

class Axis {
    Servo servo;
    int pos = 90;                            // current angle, start centered
    static constexpr int kStep = 1;          // degrees per rotate step
    static constexpr int kMin = 0;           // lower travel limit
    static constexpr int kMax = 180;         // upper travel limit
    static constexpr uint16_t kStepDelayMs = 15; // time the servo needs per step
    public:
        void setPin(int pin);
        void setMaxLeft();
        void setMaxRight();
        void rotateClockwise();        // advance ONE step toward kMax, then 15 ms settle
        void rotateCounterClockwise(); // advance ONE step toward kMin, then 15 ms settle
        int getPos() const { return pos; }
        bool atMax() const { return pos >= kMax; }
        bool atMin() const { return pos <= kMin; }
};