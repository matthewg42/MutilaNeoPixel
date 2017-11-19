#include <MutilaDebug.h>
#include <Arduino.h>
#include <Millis.h>
#include "Pulser.h"
#include "Config.h"
#include "LEDs.h"

PulserBlob::PulserBlob() : 
    _lifeMs(0),
    _blobStart(0)
{
}

void PulserBlob::startSequence()
{
    _r = random(255);
    _g = random(64);
    _b = random(255);
    _blobStart = Millis();
    _lifeMs = random(1000,3000);
    _pos = random(LED_COUNT-1);
    DB(F("PulserBlob::startSequence pos="));
    DB(_pos);
}

void PulserBlob::draw() 
{
    DB(F("PulserBlob::draw pos="));
    DB(_pos);
    DB(F(" RGB="));
    DB(_r, HEX);
    DB(' ');
    DB(_g, HEX);
    DB(' ');
    DB(_b, HEX);
    if (!active()) {
        DBLN(F(" inactive"));
        return;
    }

    float percent = (float)(Millis()-_blobStart) / _lifeMs;
    if (percent < 0.5) {
        // waxing
        percent *= 2;
        DB(F(" waxing "));
        DBLN(percent, 2);
    } else {
        // waning
        percent = 1.0-((percent-0.5)*2);
        DB(F(" waning "));
        DBLN(percent, 2);
    }
}   

const bool PulserBlob::active()
{
    return _blobStart != 0 && Millis() < _blobStart + _lifeMs;
}

Pulser::Pulser()
{
    DBLN(F("PulserBlob::PulserBlob()"));   
}

Pulser::~Pulser()
{
    LEDs.clear();
    LEDs.show();
}

void Pulser::update()
{
    // clear all pixels
    LEDs.clear();

    for(uint8_t i=0; i<NumberOfPulses; i++) {
        if (!_blobs[i].active()) {
            _blobs[i].startSequence();
        }
        _blobs[i].draw();
    }

    // update LEDs
    LEDs.show();
}




