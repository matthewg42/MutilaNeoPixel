#pragma once

#include <MutilaDebug.h>
#include "LEDStrip.h"

class Flare {
public:
    Flare(LEDStrip& LEDs) : _LEDs(LEDs) {;}
    virtual ~Flare() {;}
    virtual void update() = 0;

protected:
    LEDStrip& _LEDs;

};
