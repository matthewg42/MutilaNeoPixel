#pragma once

#include <stdint.h>
#include "Flare.h"
#include "Config.h"
#include "LEDStrip.h"

#define FLARE_SPURT_COUNT           3
#define FLARE_SPURT_DELAY           1000

class SpurtBlob {
public:
    SpurtBlob();
    void fire(uint32_t color, float velocity);
    void draw(LEDStrip& LEDs);
    const bool active(LEDStrip& LEDs);

private:
    uint32_t _color;
    float _velocity;
    float _location;
};
    
class Spurt : public Flare {
public:
    Spurt(LEDStrip& LEDs);
    virtual ~Spurt();
    void update();
    void fire(uint8_t slot);

private:
    SpurtBlob _spurts[FLARE_SPURT_COUNT];
};

