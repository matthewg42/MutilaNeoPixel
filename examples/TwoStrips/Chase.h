#pragma once

#include <stdint.h>
#include "Flare.h"
#include "LEDStrip.h"

class Chase : public Flare {
public:
    Chase(LEDStrip& LEDs);
    virtual ~Chase();
    void update();

private:
    uint16_t _chunkSize;
    unsigned long _delay;
    uint32_t _color;
    bool _divider;
    uint16_t _chunkCounter;
    unsigned long _lastUpdate;

    void display();
    void newColor();
};

