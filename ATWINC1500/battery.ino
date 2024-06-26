/* 
 *
 * This code is much easier for the M0 than for the Huzzah because the board already
 * packs a voltage divider to read the battery. See doc:
 *
 * https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/power-management
 */

float* readBatteryLevel() {
    float batteryReading = analogRead(A7);

    float batteryCharge = batteryReading;
    batteryCharge *= 2;    // we divided by 2, so multiply back
    batteryCharge *= 3.3;  // Multiply by 3.3V, our reference voltage
    batteryCharge /= 1024; // convert to voltage

    float batteryPercent = mapFloat(batteryCharge, 3.3, 4.3, 0, 100);

    float* result = new float[2];
    result[0] = batteryCharge;
    result[1] = batteryPercent;

    return result;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
