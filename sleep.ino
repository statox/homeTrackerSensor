const unsigned long oneMinute = 60e6;
const unsigned long loopDelay = 10 * oneMinute;

void sleep () {
    Serial.println();
    Serial.println("Going to sleep");
    ESP.deepSleep(loopDelay);
}
