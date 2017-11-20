#pragma once

#include <stdint.h>
#include "Flare.h"
#include "LEDStrip.h"

class PulserBlob {
public:
    PulserBlob();
    void startSequence(LEDStrip& LEDs);
    void draw(LEDStrip& LEDs);
    const bool active();

private:
    uint8_t _r;             //!< red color component
    uint8_t _g;             //!< green color component
    uint8_t _b;             //!< blue color component
    uint16_t _pos;          //!< position of center of blob (will wrap)
    uint16_t _lifeMs;       //!< how long we expect this blob to exist for
    uint32_t _blobStart;    //!< millis when we started
    uint8_t _width;         //!< how wide is a blob? 

};
    
class Pulser : public Flare {
public:
    const static uint8_t NumberOfPulses = 5;

    Pulser(LEDStrip& LEDs);
    virtual ~Pulser();
    void update();

private:
    PulserBlob _blobs[NumberOfPulses];

};

