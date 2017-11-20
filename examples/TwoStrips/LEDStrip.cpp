#include <MutilaDebug.h>
#include "LEDStrip.h"
#include "Chase.h"
#include "Rainbow.h"
#include "Pulser.h"
#include "Sparkle.h"
#include "Spurt.h"

LEDStrip::LEDStrip(uint16_t numerOfStrip1, uint8_t dataPin, neoPixelType ledType, uint8_t brightness) :
    MutilaNeoPixel(numerOfStrip1, dataPin, ledType),
    _flare(NULL),
    _flareIdx(-1)
{
    setBrightness(brightness);
    nextFlare();
}

void LEDStrip::update()
{
    if (_flare != NULL) {
        _flare->update();
    }
}

void LEDStrip::nextFlare()
{
    _flareIdx = (_flareIdx + 1) % 6;
    if (_flare != NULL) {
        delete _flare;
        _flare = NULL;
    }

    switch (_flareIdx) {
    case 0:
        DBLN(F("Index 0 = pause"));
        break;
    case 1:
        _flare = new Chase(*this);
        break;
    case 2:
        _flare = new Rainbow(*this);
        break;
    case 3:
        _flare = new Pulser(*this);
        break;
    case 4:
        _flare = new Sparkle(*this);
        break;
    case 5:
        _flare = new Spurt(*this);
        break;
    default:
        DBLN(F("Unknown flare ID: "));
        DBLN(_flareIdx);
    }
}


