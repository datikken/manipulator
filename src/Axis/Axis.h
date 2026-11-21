#pragma once

#include <Arduino.h>
#include <Servo.h>

class Axis {
    Servo servo;
    int pos = 90;                            // current angle, start centered
    static constexpr int kStep = 1;          // degrees per rotate step
    static constexpr int kMin = 0;           // lower travel limit
    static constexpr int kMax = 180;         // upper travel limit
    static constexpr uint16_t kDefaultStepDelayMs = 15; // fallback settle time

    public:
        void setPin(int pin);
        void setMaxLeft();
        void setMaxRight();
        // advance ONE step toward the limit, then wait stepDelayMs (higher = slower)
        void rotateClockwise(uint16_t stepDelayMs = kDefaultStepDelayMs);
        void rotateCounterClockwise(uint16_t stepDelayMs = kDefaultStepDelayMs);
        int getPos() const { return pos; }
        bool atMax() const { return pos >= kMax; }
        bool atMin() const { return pos <= kMin; }
};
