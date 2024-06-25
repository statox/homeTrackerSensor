#include <WiFi101.h>
#include <ArduinoLowPower.h>

const unsigned long oneMinute = 60e3;
const unsigned long loopDelay = 10 * oneMinute;

void sleep () {
    Serial.println();
    Serial.println("Going to sleep");

    WiFi.end();
    LowPower.deepSleep(loopDelay);
}
