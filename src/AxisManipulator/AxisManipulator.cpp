#include "AxisManipulator.h"

AxisManipulator::AxisManipulator(Axis& axis, int center, int deadZone)
    : axis_(axis), center_(center), deadZone_(deadZone) {}

void AxisManipulator::update(int valX) {
    const int delta = valX - center_; // negative = below default, positive = above

    if (delta < -deadZone_) {
        // joystick pulled below the default position -> counter-clockwise
        axis_.rotateCounterClockwise();
    } else if (delta > deadZone_) {
        // joystick pushed above the default position -> clockwise
        axis_.rotateClockwise();
    }
    // else: centered / inside dead zone -> hold position
}
