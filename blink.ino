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
