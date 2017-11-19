#pragma once

#include <stdint.h>
#include "Flare.h"
#include "Config.h"

#define FLARE_SPURT_COUNT           3
#define FLARE_SPURT_DELAY           200
#define FLARE_SPURT_VEL_MIN         (LED_COUNT/30)
#define FLARE_SPURT_VEL_MAX         LED_COUNT

class SpurtBlob {
public:
    SpurtBlob();
    void fire(uint32_t color, float velocity);
    void draw();
    const bool active() { return _location < LED_COUNT; }

private:
    uint32_t _color;
    float _velocity;
    float _location;
};
    
class Spurt : public Flare {
public:
    Spurt();
    virtual ~Spurt();
    void update();
    void fire(uint8_t slot);

private:
    SpurtBlob _spurts[FLARE_SPURT_COUNT];
};

