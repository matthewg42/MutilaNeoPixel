#include <Arduino.h>
#include <Heartbeat.h>
#include <MutilaNeoPixel.h>
#include <MutilaDebug.h>
#include <stdint.h>
#include "Strip1.h"
#include "Strip2.h"
#include "Button1.h"
#include "Button2.h"
#include "Config.h"
#include "Flare.h"
#include "Chase.h"

Heartbeat heartbeat(13);

void setup()
{
    Serial.begin(115200);
    heartbeat.begin();
    Button1.begin();
    Button2.begin();
    Strip1.begin();
    Strip2.begin();
    DBLN(F("setup:E"));
}

void loop()
{
    heartbeat.update();
    Button1.update();
    Button2.update();
    Strip1.update();
    Strip2.update();

    if (Button1.tapped()) {
        DBLN(F("Button1 pressed"));
        Strip1.nextFlare();
    }

    if (Button2.tapped()) {
        DBLN(F("Button2 pressed"));
        Strip2.nextFlare();
    }
}

