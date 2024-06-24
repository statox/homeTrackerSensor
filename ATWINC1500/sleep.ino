#include <WiFi101.h>

const unsigned long oneMinute = 60e3;
const unsigned long loopDelay = 10 * oneMinute;

void initSleep() {
    WiFi.lowPowerMode();
}

void sleep () {
    Serial.println();
    Serial.println("Going to sleep");

    delay(loopDelay);
}
