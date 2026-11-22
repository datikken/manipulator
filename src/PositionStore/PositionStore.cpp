#include "PositionStore.h"
#include <EEPROM.h>

PositionStore::PositionStore(Axis& axisX, Axis& axisY)
    : axisX_(axisX),
      axisY_(axisY),
      lastSavedX_(-1),      // -1 = nothing saved to EEPROM yet
      lastSavedY_(-1),
      lastChangeMs_(0),
      dirty_(false) {}

uint8_t PositionStore::encode(int angle) {
    return static_cast<uint8_t>(constrain(angle, 0, 180));
}

int PositionStore::decode(uint8_t raw) {
    // guard against a corrupted / never-written value
    return constrain(static_cast<int>(raw), 0, 180);
}

bool PositionStore::hasSavedData() const {
    return EEPROM.read(kEepromAddrMagic) == kMagic;
}

void PositionStore::restore() {
    if (!hasSavedData()) {
        // EEPROM never written (fresh board) -> keep the axes at their defaults
        lastSavedX_ = -1;
        lastSavedY_ = -1;
        return;
    }

    const int x = decode(EEPROM.read(kEepromAddrX));
    const int y = decode(EEPROM.read(kEepromAddrY));

    axisX_.setPos(x);
    axisY_.setPos(y);

    lastSavedX_ = x;
    lastSavedY_ = y;
    dirty_ = false;
}

void PositionStore::update() {
    const int x = axisX_.getPos();
    const int y = axisY_.getPos();

    if (x != lastSavedX_ || y != lastSavedY_) {
        // position changed since the last save -> (re)start the debounce timer
        if (!dirty_) {
            dirty_ = true;
            lastChangeMs_ = millis();
        }

        // save only after the servos have been still for kSaveDebounceMs
        if (millis() - lastChangeMs_ >= kSaveDebounceMs) {
            saveNow();
        }
    } else {
        dirty_ = false; // back to the saved value, nothing pending
    }
}

void PositionStore::saveNow() {
    const int x = axisX_.getPos();
    const int y = axisY_.getPos();

    EEPROM.update(kEepromAddrMagic, kMagic); // .update() writes only if changed
    EEPROM.update(kEepromAddrX, encode(x));
    EEPROM.update(kEepromAddrY, encode(y));

    lastSavedX_ = x;
    lastSavedY_ = y;
    dirty_ = false;
}
