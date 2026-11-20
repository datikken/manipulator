#include "Joystick.h"

void Joystick::activateBtn() {
    pinMode(axisZ, INPUT_PULLUP);
}

int Joystick::getValX() {
    return analogRead(axisX);
}

int Joystick::getValY() {
    return analogRead(axisY);
}

int Joystick::getValZ() {
    return digitalRead(axisZ) == LOW ? 1 : 0; // 1 = нажата
}
