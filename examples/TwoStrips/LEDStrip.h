#pragma once

#include <stdint.h>
#include <MutilaNeoPixel.h>

class Flare;

class LEDStrip : public MutilaNeoPixel {
public:
    LEDStrip(uint16_t numerOfStrip1, uint8_t dataPin, neoPixelType ledType=NEO_GRB+NEO_KHZ800, uint8_t brightness=255);
    void update();
    void nextFlare();

private:
    Flare* _flare;
    int8_t _flareIdx;

};

