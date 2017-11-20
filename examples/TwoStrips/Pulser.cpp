#include <MutilaDebug.h>
#include <Arduino.h>
#include <Millis.h>
#include "Pulser.h"
#include "Config.h"

PulserBlob::PulserBlob() : 
    _lifeMs(0),
    _blobStart(0)
{
}

void PulserBlob::startSequence(LEDStrip& LEDs)
{
    _r = random(200) + 55;
    _g = random(128);
    _b = random(100) + 155;
    _blobStart = Millis();
    _lifeMs = random(1000, 10000);
    _pos = random(LEDs.numPixels()-1);
    _width = random(1, 8);
    //DB(F("PulserBlob::startSequence pos="));
    //DB(_pos);
    //DB(F("width="));
    //DB(_width);
    //DB(F(" RGB="));
    //DB(_r, HEX);
    //DB(' ');
    //DB(_g, HEX);
    //DB(' ');
    //DBLN(_b, HEX);
}

void PulserBlob::draw(LEDStrip& LEDs) 
{
    if (!active()) {
        return;
    }

    float percent = (float)(Millis()-_blobStart) / _lifeMs;
    if (percent < 0.5) {
        // waxing
        percent *= 2;
    } else {
        // waning
        percent = 1.0-((percent-0.5)*2);
    }
    // draw central pixel
    LEDs.setPixelColor(_pos, _r*percent, _g*percent, _b*percent);

    // draw pixels either size of the central one
    float sideBright = 0.90;
    for (uint8_t i=1; i<=_width; i++) {
        LEDs.setPixelColor((_pos + LEDs.numPixels() - i) % LEDs.numPixels(), _r*percent*sideBright, _g*percent*sideBright, _b*percent*sideBright);
        sideBright = sideBright * sideBright * sideBright;
    }
}   

const bool PulserBlob::active()
{
    return _blobStart != 0 && Millis() < _blobStart + _lifeMs;
}

Pulser::Pulser(LEDStrip& LEDs) :
    Flare(LEDs)
{
    DBLN(F("PulserBlob::PulserBlob()"));   
}

Pulser::~Pulser()
{
    _LEDs.clear();
    _LEDs.show();
}

void Pulser::update()
{
    // clear all pixels
    _LEDs.clear();

    for(uint8_t i=0; i<NumberOfPulses; i++) {
        if (!_blobs[i].active()) {
            _blobs[i].startSequence(_LEDs);
        }
        _blobs[i].draw(_LEDs);
    }

    // update LEDs
    _LEDs.show();
}




