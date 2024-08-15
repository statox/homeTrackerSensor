#include <ArduinoLowPower.h>
#include <WiFi101.h>

const unsigned long oneSecond = 1e3;
const unsigned long loopDelay = CONFIG_SLEEP_SECONDS * oneSecond;

void sleep() {
    Serial.println();
    Serial.print("Going to sleep for (s) ");
    Serial.println(CONFIG_SLEEP_SECONDS);

    WiFi.end();
    LowPower.deepSleep(loopDelay);
}

void shutdown() {
    Serial.println();
    Serial.println("Shuting down (infinite deepsleep) ");

    WiFi.end();
    LowPower.deepSleep();
}
