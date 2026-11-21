#pragma once

#include <Arduino.h>
#include "Axis/Axis.h"

// Drives an Axis from a joystick X reading.
//
// The joystick reports 0..1023 with ~512 at rest. We treat the resting value as
// the "default position" and compare each new reading against it:
//   - valX < center (below default)  -> rotate counter-clockwise toward kMin
//   - valX > center (above default)  -> rotate clockwise toward kMax
//   - valX == center / inside dead zone -> hold still
//
// Rotation is non-blocking: update() advances the Axis by at most ONE step per
// call, so loop() keeps running (joystick, serial, etc.) between steps.
class AxisManipulator {
    Axis& axis_;

    int center_;          // joystick resting value (default position)
    int deadZone_;        // +/- window around center treated as "no movement"

public:
    AxisManipulator(Axis& axis, int center = 512, int deadZone = 30);

    // Feed the latest joystick X value. Advances the axis by one step in the
    // requested direction, or does nothing when centered / inside dead zone.
    void update(int valX);

    // Re-calibrate the resting value (e.g. from a measured idle reading).
    void setCenter(int center) { center_ = center; }

    int getCenter() const { return center_; }
};
