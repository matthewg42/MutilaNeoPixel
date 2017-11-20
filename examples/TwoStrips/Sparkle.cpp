#include <Arduino.h>
#include <MutilaDebug.h>
#include "Sparkle.h"
#include "Config.h"

Sparkle::Sparkle(LEDStrip& LEDs) :
    Flare(LEDs),
    _lastUpdate(0)
{
    DBLN(F("Sparkle::Sparkle()"));   
}

Sparkle::~Sparkle()
{
    _LEDs.clear();
    _LEDs.show();
}

void Sparkle::update()
{
    if (millis() < _lastUpdate + FLARE_SPARKLE_UPDATE_MS) {
        return;
    }
    _lastUpdate = millis()+FLARE_SPARKLE_UPDATE_MS;
    display();
}

void Sparkle::display()
{
    uint16_t i = random(0, _LEDs.numPixels());
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
    switch (random(15+FLARE_SPARKLE_DARKENING)) {
    case 0:
        g = 220;
        break;
    case 1:
        r = 220;
        break;
    case 2:
    case 3:
    case 4:
        r = 80;
        g = 128;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        r = 30;
        g = 70;
        b = 205;
        break;
    default:
        r = 0;
        g = 0;
        b = 0;
    }

    _LEDs.setPixelColor(i, r, g, b);
    r /= 3;
    g /= 3;
    b /= 3;
    if (i > 0) _LEDs.setPixelColor(i-1, r, g, b);
    if (i < _LEDs.numPixels()-1) _LEDs.setPixelColor(i+1, r, g, b);

    for(i=0; i<_LEDs.numPixels(); i++) {
        const uint32_t color = _LEDs.getPixelColor(i);
        r = color >> 16;
        g = (color - r) >> 8;
        b = color % 256;
        if (r > 0) r--;
        if (g > 0) g--;
        if (b > 0) b--;
        _LEDs.setPixelColor(i, r, g, b);
    }
    _LEDs.show();
}

