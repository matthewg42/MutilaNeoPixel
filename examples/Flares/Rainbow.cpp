#include <MutilaDebug.h>
#include "Rainbow.h"
#include "Config.h"
#include "LEDs.h"

Rainbow::Rainbow() :
    _lastUpdate(0),
    _pos(0)
{
    DBLN(F("Rainbow::Rainbow()"));   
}

Rainbow::~Rainbow()
{
}

void Rainbow::update()
{
    uint16_t elapsed = millis() - _lastUpdate;
    if (elapsed < 5) {
        return;
    }
    _lastUpdate = millis();
    display();
}

// Slightly different, this makes the rainbow equally distributed throughout
void Rainbow::display() {
    for(uint16_t i=0; i<LED_COUNT; i++) {
        //LEDs.setPixelColor(i, Wheel((i+LED_COUNT) & 255));
        LEDs.setPixelColor(i, Wheel(((i * 256 / LED_COUNT) + _pos) & 255));
    }
    _pos++;
    LEDs.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Rainbow::Wheel(uint8_t WheelPos) 
{
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return LEDs.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return LEDs.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
    }
    WheelPos -= 170;
    return LEDs.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}


