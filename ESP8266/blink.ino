// On Adafruit Feather Huzzah ESP8266 the pin 0 is connected
// to the built-in onboard red led
// Setting the pin to LOW turns the led on

void initBlink() {
    pinMode(0, OUTPUT);
}

void blink(int times, int length, int interval) {
    Serial.print("Blink");

    for (int i=0; i<times; i++) {
        Serial.print(".");
        digitalWrite(0, LOW);
        delay(length);
        digitalWrite(0, HIGH);
        delay(interval);
    }
    Serial.println();
}
