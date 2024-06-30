#include <WiFi101.h>
#include <ArduinoLowPower.h>

const unsigned long oneSecond = 1e3;
const unsigned long loopDelay = CONFIG_SLEEP_SECONDS * oneSecond;

void sleep () {
    Serial.println();
    Serial.print("Going to sleep for (s) ");
    Serial.print(CONFIG_SLEEP_SECONDS);

    WiFi.end();
    LowPower.deepSleep(loopDelay);
}
