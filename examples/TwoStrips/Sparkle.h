#pragma once

#include <stdint.h>
#include "Flare.h"
#include "LEDStrip.h"

#define FLARE_SPARKLE_DARKENING     5
#define FLARE_SPARKLE_UPDATE_MS     10

class Sparkle : public Flare {
public:
    Sparkle(LEDStrip& LEDs);
    virtual ~Sparkle();
    void update();

private:
    unsigned long _lastUpdate;
    void display();
};
