#pragma once

#include <Arduino.h>
#include "Axis/Axis.h"

// Persists the X and Y servo positions to the Arduino's onboard EEPROM so the
// servos come back to the same place after a reboot or power loss.
//
// NOTE: an Arduino Uno has no filesystem. EEPROM (512 bytes on the 328P) is the
// correct mechanism — it survives resets and power cycles.
//
// EEPROM layout used by this class:
//   byte 0 : magic marker (kMagic)       - tells us the stored data is valid
//   byte 1 : X angle (0..180)
//   byte 2 : Y angle (0..180)
//
// Writes are only performed when a value actually changed, and are debounced so
// that a servo sweeping through hundreds of steps does not wear out the EEPROM
// (rated ~100k write cycles per cell).
class PositionStore {
    Axis& axisX_;
    Axis& axisY_;

    int lastSavedX_;                  // last position known to be in EEPROM
    int lastSavedY_;
    unsigned long lastChangeMs_;      // when a change was first seen
    bool dirty_;                      // a change is pending a save

    static constexpr int kEepromAddrMagic = 0;
    static constexpr int kEepromAddrX = 1;
    static constexpr int kEepromAddrY = 2;
    static constexpr uint8_t kMagic = 0xA5;  // marks "EEPROM contains valid data"
    static constexpr unsigned long kSaveDebounceMs = 3000; // save 3 s after motion stops

    static uint8_t encode(int angle);
    static int decode(uint8_t raw);

public:
    PositionStore(Axis& axisX, Axis& axisY);

    // Call once in setup() AFTER the axes are attached. Restores the saved
    // positions to the servos (or leaves the default when EEPROM is empty).
    void restore();

    // Call every loop() pass. Detects position changes and saves them to EEPROM
    // once the servos have stopped moving for kSaveDebounceMs.
    void update();

    // Force an immediate save of the current positions.
    void saveNow();

    // True when EEPROM held valid data at the last restore().
    bool hasSavedData() const;
};
