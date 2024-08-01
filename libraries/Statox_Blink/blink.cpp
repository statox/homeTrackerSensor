#include <Arduino.h>

#if defined(ARDUINO_SAMD_ADAFRUIT)
// On Adafruit Feather M0 ATWINC1500 the pin 0 is connected
// to the built-in onboard red led
// Setting the pin to LOW turns the led on
const int LED_PIN = 13;
const int ON = HIGH;
const int OFF = LOW;
#else
// NOT USED ANYMORE
// On Adafruit Feather Huzzah ESP8266 the pin 0 is connected
// to the built-in onboard red led
// Setting the pin to LOW turns the led on
const int LED_PIN = 0;
const int ON = LOW;
const int OFF = HIGH;
#endif

void initBlink() {
    pinMode(LED_PIN, OUTPUT);
}

void blink(int times, int length, int interval) {
    Serial.println();
    Serial.print("Blink");

    for (int i=0; i<times; i++) {
        Serial.print(".");
        digitalWrite(LED_PIN, ON);
        delay(length);
        digitalWrite(LED_PIN, OFF);
        delay(interval);
    }
    Serial.println();
}
