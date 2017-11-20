#pragma once

#include <stdint.h>
#include "Flare.h"
#include "LEDStrip.h"

class Rainbow : public Flare {
public:
    Rainbow(LEDStrip& LEDs);
    virtual ~Rainbow();
    void update();

private:
    unsigned long _lastUpdate;
    uint16_t _pos;

    void display();
    uint32_t Wheel(uint8_t WheelPos);

};
