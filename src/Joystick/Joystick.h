#pragma once

#include <Arduino.h>

class Joystick {
    static constexpr uint8_t axisX = A0; // ось Х
    static constexpr uint8_t axisY = A1; // ось Y
    static constexpr uint8_t axisZ = 2;  // кнопка джойстика (D2)

public:
    void activateBtn();
    void debugPotentiomter();
    int getValX();
    int getValY();
    int getValZ();
};
