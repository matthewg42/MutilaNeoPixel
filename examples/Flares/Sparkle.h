#pragma once

#include "Flare.h"
#include <stdint.h>

#define FLARE_SPARKLE_DARKENING     5
#define FLARE_SPARKLE_UPDATE_MS     10

class Sparkle : public Flare {
public:
    Sparkle();
    virtual ~Sparkle();
    void update();

private:
    unsigned long _lastUpdate;
    void display();
};
