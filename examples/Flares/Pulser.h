#pragma once

#include <stdint.h>
#include "Flare.h"
#include "Config.h"

class PulserBlob {
public:
    PulserBlob();
    void startSequence();
    void draw();
    const bool active();

private:
    uint8_t _r;             //!< red color component
    uint8_t _g;             //!< green color component
    uint8_t _b;             //!< blue color component
    uint16_t _pos;          //!< position of center of blob (will wrap)
    uint16_t _lifeMs;       //!< how long we expect this blob to exist for
    uint32_t _blobStart;    //!< millis when we started

};
    
class Pulser : public Flare {
public:
    //const uint8_t NumberOfPulses = (LED_COUNT/10)+1;
    const static uint8_t NumberOfPulses = 1;

    Pulser();
    virtual ~Pulser();
    void update();

private:
    PulserBlob _blobs[NumberOfPulses];

};

