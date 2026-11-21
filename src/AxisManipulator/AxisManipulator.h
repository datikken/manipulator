#pragma once

#include <Arduino.h>
#include "Axis/Axis.h"

// Drives an Axis from a joystick reading.
//
// The joystick reports 0..1023 with ~512 at rest. We treat the resting value as
// the "default position" and compare each new reading against it:
//   - val < center (below default)  -> rotate counter-clockwise toward kMin
//   - val > center (above default)  -> rotate clockwise toward kMax
//   - val == center / inside dead zone -> hold still
//
// How far the stick is pushed selects one of three speeds (smaller delay = faster):
//   |val - center| > 600 -> 5 ms per step (slow)
//   |val - center| > 800 -> 2 ms per step
//   |val - center| > 1000 -> 0 ms per step (fast, no settle wait)
//
// Rotation is non-blocking: update() advances the Axis by at most ONE step per
// call, so loop() keeps running (joystick, serial, etc.) between steps.
class AxisManipulator {
    Axis& axis_;

    int center_;          // joystick resting value (default position)
    int deadZone_;        // +/- window around center treated as "no movement"

    // Speed tiers in ADC units away from center, and matching step delays.
    static constexpr int kSpeedTier1 = 1;   // > 600  -> kDelay1
    static constexpr int kSpeedTier2 = 500;   // > 800  -> kDelay2
    static constexpr int kSpeedTier3 = 1000;  // > 1000 -> kDelay3
    static constexpr uint16_t kDelay1 = 5;
    static constexpr uint16_t kDelay2 = 2;
    static constexpr uint16_t kDelay3 = 0;

public:
    AxisManipulator(Axis& axis, int center = 512, int deadZone = 30);

    // Feed the latest joystick value. Advances the axis by one step at the speed
    // selected by how far the stick is pushed, or holds still when centered.
    void update(int val);

    // Delay chosen for the given reading (exposed for testing/debugging).
    uint16_t speedDelayFor(int val) const;

    // Re-calibrate the resting value (e.g. from a measured idle reading).
    void setCenter(int center) { center_ = center; }

    int getCenter() const { return center_; }
};

