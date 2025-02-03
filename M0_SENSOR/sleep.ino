#include <ArduinoLowPower.h>
#include <WiFi101.h>

#define DEFAULT_SLEEP_SECONDS 60 * 10

const unsigned long oneSecond = 1e3;
const unsigned long defaultSleepTime = DEFAULT_SLEEP_SECONDS * oneSecond;

void sleep() {
    sleep(DEFAULT_SLEEP_SECONDS);
}

void sleep(int seconds) {
    // If sleep time is less than one second or more than 10 days we
    // probably messed up something
    if (seconds < 1 || seconds > 3600 * 24 * 10) {
        seconds = DEFAULT_SLEEP_SECONDS;
    }
    Serial.println();
    Serial.print("Going to sleep for (s) ");
    Serial.println(seconds);

    WiFi.end();
    LowPower.deepSleep(seconds * oneSecond);
}

void shutdown() {
    Serial.println();
    Serial.println("Shuting down (infinite deepsleep) ");

    WiFi.end();
    LowPower.deepSleep();
}
