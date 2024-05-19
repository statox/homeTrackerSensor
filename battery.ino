/*
 * Inspired by
 * - https://learn.adafruit.com/using-ifttt-with-adafruit-io/wiring#battery-tracking
 * - https://learn.adafruit.com/using-ifttt-with-adafruit-io/arduino-code-2
 *
 * Use Feather Bat pin to get the Vout of the battery, run it through a tension divisor
 * bridge with 1M and 200K resistances and plug the Vout of the bridge on the
 * analog A0 port
 */
int* readBatteryLevel() {
    // read the battery level from the ESP8266 analog in pin.
    // analog read level is 10 bit 0-1023 (0V-1V).
    // our 1M & 200K voltage divider takes the max
    // lipo value of 4.2V and drops it to 0.7V max.
    // this means our min analog read value should be 520 (3.14V)
    // and the max analog read value should be 700 (4.2V).
    //
    // Values adjusted for actual measurements (520 -> 498; 700->694)
    int batteryReading = analogRead(A0);

    // convert battery level to percent
    int batteryPercent = map(batteryReading, 498, 694, 0, 100);

    int* result = new int[2];
    result[0] = batteryReading;
    result[1] = batteryPercent;

    return result;
}
