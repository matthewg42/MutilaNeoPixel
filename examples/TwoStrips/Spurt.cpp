#include <MutilaDebug.h>
#include <Arduino.h>
#include "Spurt.h"
#include "Config.h"

SpurtBlob::SpurtBlob() :
    _location(1000)
{
}

void SpurtBlob::fire(uint32_t color, float velocity)
{
    _color = color;
    _velocity = velocity;
    _location = 0.0;
}

void SpurtBlob::draw(LEDStrip& LEDs) 
{
    if (active(LEDs)) {
        // get the current RGB values for existing pixel and this SpurtBlob
        uint32_t color = LEDs.getPixelColor((uint16_t)_location);
        uint8_t cr = color >> 16;
        uint8_t cg = (color >> 8) % 256;
        uint8_t cb = color % 256;
        uint8_t br = _color >> 16;
        uint8_t bg = (_color >> 8) % 256;
        uint8_t bb = _color % 256;

        // Set the new pixel RGB as the max of the existing and SpurtBlob colors
        // This is a very primative form of mixing I guess!
        LEDs.setPixelColor((uint16_t)_location, 
            cr > br ? cr : br,
            cg > bg ? cg : bg,
            cb > bb ? cb : bb);
        _location += _velocity;
    }
}   

const bool SpurtBlob::active(LEDStrip& LEDs) 
{ 
    return _location < LEDs.numPixels(); 
}

Spurt::Spurt(LEDStrip& LEDs) :
    Flare(LEDs)
{
    DBLN(F("SpurtBlob::SpurtBlob()"));   
    fire(0);
}

Spurt::~Spurt()
{
    _LEDs.clear();
    _LEDs.show();
}

void Spurt::update()
{
    // fade all pixels
    uint8_t r;
    uint8_t g;
    uint8_t b;
    for(uint16_t i=0; i<_LEDs.numPixels(); i++) {
        const uint32_t color = _LEDs.getPixelColor(i);
        r = color >> 16;
        g = (color >> 8) % 256;
        b = color % 256;
        if (r > 0) r--;
        if (g > 0) g--;
        if (b > 0) b--;
        _LEDs.setPixelColor(i, r, g, b);
    }

    // update active spurts, and determine active count
    uint8_t count = 0;
    int8_t inactiveIdx = 0;
    for (uint8_t i=0; i<FLARE_SPURT_COUNT; i++) {
        if (_spurts[i].active(_LEDs)) {
            count++;
        } else {
            // if any inactive, we mark the last one for possible use
            inactiveIdx = i;
        }
    }

    // decide if we want to start a new spurt
    if (count < FLARE_SPURT_COUNT) {
        if (random(FLARE_SPURT_DELAY) == 0 || count == 0) {
            fire(inactiveIdx);
        }
    }

    // plot active spurts
    for (uint8_t i=0; i<FLARE_SPURT_COUNT; i++) {
        _spurts[i].draw(_LEDs);
    }

    _LEDs.show();

}

void Spurt::fire(uint8_t slot)
{
    uint32_t r = random(255);
    uint16_t g = random(255);
    uint32_t b = random(255);
    uint32_t col = (r<<16) + (g<<8) + b; 
    float vel = random((_LEDs.numPixels()/30), _LEDs.numPixels())/200.;
    DB(F("FIRE col=0x"));
    DB(col, HEX);
    DB(F(" vel="));
    DBLN(vel, 5);
    _spurts[slot].fire(col, vel);

}

