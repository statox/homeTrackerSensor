#include "BatteryManager.h"
#include <Arduino.h>

BatteryManager::BatteryManager(int batteryPin): batteryPin(batteryPin) { }

void BatteryManager::initializeData() {
    batteryData.charge = 0.0;
    batteryData.percent = 0.0;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* 
 *
 * This code is much easier for the M0 than for the Huzzah because the board already
 * packs a voltage divider to read the battery. See doc:
 *
 * https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/power-management
 */
void BatteryManager::updateData() {
    float batteryReading = analogRead(batteryPin);

    float batteryCharge = batteryReading;
    batteryCharge *= 2;    // we divided by 2, so multiply back
    batteryCharge *= 3.3;  // Multiply by 3.3V, our reference voltage
    batteryCharge /= 1024; // convert to voltage

    batteryData.charge = batteryCharge;
    batteryData.percent = mapFloat(batteryCharge, 3.3, 4.3, 0, 100);
}

bool BatteryManager::mustShutdown() {
    // Less than 3V is low battery, more than 4.5V is invalid reading
    return batteryData.charge < 3.5 || batteryData.charge > 4.5;
}
