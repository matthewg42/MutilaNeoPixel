#include <Arduino.h>
#include <Heartbeat.h>
#include <MutilaNeoPixel.h>
#include <MutilaDebug.h>
#include <stdint.h>
#include "Button.h"
#include "LEDs.h"
#include "Config.h"
#include "Flare.h"
#include "Chase.h"
#include "Spurt.h"
#include "Sparkle.h"
#include "Rainbow.h"

Heartbeat heartbeat(13);
Flare* flare = NULL;
uint8_t flareID = 3;

void nextFlare()
{
    if (flare) {
        delete flare;
    }
    flareID = (flareID+1) % 4;
    switch (flareID) {
    case 0:
        flare = new Chase(LED_COUNT/8, 30);
        break;
    case 1:
        flare = new Rainbow();
        break;
    case 2:
        flare = new Spurt();
        break;
    case 3:
        flare = new Sparkle();
        break;
    default:
        DBLN("unknown flareID");
        break;
    }
}

void setup()
{
    Serial.begin(115200);
    heartbeat.begin();
    Button.begin();
    LEDs.begin();
    LEDs.setBrightness(LED_BRIGHTNESS);
    LEDs.clear();
    LEDs.show();
    nextFlare();
    Serial.println(F("setup:E"));
}

void loop()
{
    Button.update();
    heartbeat.update();
    flare->update();

    if (Button.tapped()) {
        DBLN("tap");
        nextFlare();
    }
}

