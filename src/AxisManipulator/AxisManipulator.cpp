#include "AxisManipulator.h"

AxisManipulator::AxisManipulator(Axis& axis, int center, int deadZone)
    : axis_(axis), center_(center), deadZone_(deadZone) {}

uint16_t AxisManipulator::speedDelayFor(int val) const {
    const int strength = abs(val - center_); // how far the stick is pushed
    if (strength > kSpeedTier3) return kDelay3; // > 1000 -> 0 ms (no wait)
    if (strength > kSpeedTier2) return kDelay2; // > 800  -> 2 ms
    if (strength > kSpeedTier1) return kDelay1; // > 600  -> 5 ms
    return kDelay1;                             // below first tier: slowest
}

void AxisManipulator::update(int val) {
    const int delta = val - center_; // negative = below default, positive = above

    if (delta < -deadZone_) {
        // joystick pulled below the default position -> counter-clockwise
        axis_.rotateCounterClockwise(speedDelayFor(val));
    } else if (delta > deadZone_) {
        // joystick pushed above the default position -> clockwise
        axis_.rotateClockwise(speedDelayFor(val));
    }
    // else: centered / inside dead zone -> hold position
}

