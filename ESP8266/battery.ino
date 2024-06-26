/*
 * Inspired by
 * - https://learn.adafruit.com/using-ifttt-with-adafruit-io/wiring#battery-tracking
 * - https://learn.adafruit.com/using-ifttt-with-adafruit-io/arduino-code-2
 *
 * Use Feather Bat pin to get the Vout of the battery, run it through a tension divisor
 * bridge with 1M and 200K resistances and plug the Vout of the bridge on the
 * analog A0 port
 */
float* readBatteryLevel() {
    // Instead of using a manual voltage divider I probably want to use
    // ESP.getVCC() directly
    // cf:
    // https://arduino-esp8266.readthedocs.io/en/latest/reference.html#analog-input
    // https://github.com/esp8266/Arduino/issues/721#issuecomment-206524786

    // It seems that the A0 pin gives incorrect but consistent values
    // (For example for a Vr2=0.69V I get A0 reading = 752 (When I would expectd 0.69*1023 = 705)
    // This guy seems to say that it happens on a lot of ESP8266 and can be corrected with an offset
    // https://github.com/esp8266/Arduino/issues/721#issuecomment-206480211

    // read the battery level from the ESP8266 analog in pin and computes human readable levels
    //
    // Schema:
    //           ----       ----
    //  GND ||--| R2 |--*--| R1 |---> Vbat
    //           ‾‾‾‾   |   ‾‾‾‾
    //                 Vr2 (Analog pin A0)
    //
    // Formula:
    //
    // Vr2 = (Vbat * R2) / (R1 + R2)
    //
    // Data:
    // R1 = 1000KΩ (1MΩ)
    // R2 = 200KΩ
    //
    // Battery Charge range: 3.3V - 4.3V
    //      It could go below but that would be unsafe we want to cut a 3.3V
    //      In theory the max is 4.2V but when fully charged I get readings 4.2<x<4.3 so using 4.3 as max
    //
    // So Vr2 range: 0.71V - 0.55V
    //
    // Since A0 reads voltage between 0V-1V and maps it to 0-1023:
    // Reading of A0 range: 562 - 726
    //
    // So:
    //  Battery Current Percentage = map reading 562->726 to 0%->100%
    //  Battery Current Charge = map reading 562->726 to 3.3V->4.3V

    // -37 for sensor1, -47 for sensor2
    int adcOffset = -47;
    float batteryReading = float(analogRead(A0) + adcOffset);
    float batteryPercent = mapFloat(batteryReading, 562, 726, 0, 100);
    float batteryCharge = mapFloat(batteryReading, 562, 726, 3.3, 4.3);

    float* result = new float[2];
    result[0] = batteryCharge;
    result[1] = batteryPercent;

    return result;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
