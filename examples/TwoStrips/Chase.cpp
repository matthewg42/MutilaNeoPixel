#include <Arduino.h>
#include <Millis.h>
#include <MutilaDebug.h>
#include "Chase.h"
#include "Config.h"

Chase::Chase(LEDStrip& LEDs) :
    Flare(LEDs),
    _chunkSize((LEDs.numPixels()/5)+2),
    _delay(30),
    _divider(false)
{
    DBLN(F("Chase::Chase()"));   
    newColor();
    _lastUpdate = Millis();
}

Chase::~Chase()
{
    _LEDs.clear();
    _LEDs.show();
}

void Chase::newColor()
{
    uint32_t r = random(256)/(_divider?4:1);
    uint16_t g = random(256)/(_divider?4:1);
    uint8_t  b = random(256)/(_divider?4:1);
    _color = (r<<16) + (g<<8) + b;
    _chunkCounter = _chunkSize;
    _divider = !_divider;
}

void Chase::update()
{
    if (_lastUpdate + _delay > Millis()) {
        return;
    }
    _lastUpdate = Millis();

    if (_chunkCounter-- == 0) {
        newColor();
    }

    // Move existing colours along one pixel
    for (uint16_t i=_LEDs.numPixels()-1; i>0; i--) {
        _LEDs.setPixelColor(i, _LEDs.getPixelColor(i-1));
    }

    // Set first pixel to current pixel color
    _LEDs.setPixelColor(0, _color);
    _LEDs.show();
}


