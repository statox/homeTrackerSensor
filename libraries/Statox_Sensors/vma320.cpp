/*
 * Code for the VMA320 temperature sensor
 * https://www.velleman.eu/products/view/?country=be&lang=fr&id=435554
 *
 * IMPORTANT
 * We end up not using this sensor because it requires an analogue port
 * which we'll want to use to measure the battery level.
 * Also the readings seems less stable than the DHT11/22 and are probably
 * less precise because of the homemade tension division
 *
 * This sensor uses the only analogue PIN of the ESP8266
 * Important note: On ESP8266 the analogue pin is limited to 1V input
 * but the VMA320 will return up to 3V when run with the ESP8266 3V logic.
 * So to use the sensor properly we need to use a pont diviseur de tension.
 * (See picture in this folder for schematics CAUTION In the schema I thought the
 * output of ESP8266 was 3.3V but it really is 3V)
 */

#include <Arduino.h>
#include <math.h>

#define VMA320_PIN A0 // Input PIN: ADC (The only analogue pin on ESP8266)

// Based on https://stackoverflow.com/a/44932077/4194289
double analogToCelsius(int RawADC) {
    double Temp;
    Temp = log(10000.0 / (1024.0 / RawADC - 1)); // for pull-up configuration
    Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
    Temp = Temp - 273.15; // Convert Kelvin to Celcius
    return Temp;
}

double readVMA320() {
    int sensorvalue = analogRead(VMA320_PIN);
    double celsius = analogToCelsius(sensorvalue);

    return celsius;
}
