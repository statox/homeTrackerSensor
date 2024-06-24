#include "arduino_secrets.h"
#include <ArduinoJson.h>
#include "Statox_Sensors.h"
#include "Statox_Blink.h"

const char* sensorName = "dev-sensor-3";

void setup() {
    Serial.begin(9600);
    while(!Serial) { }

    initBlink();
    blink(10, 100, 100);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("===== Restart ======");
    Serial.println();

    initSHT31();

    Serial.println();
    blink(2, 500, 500);

    float* shtReadings = readSHT31();
    float shtCelsius = shtReadings[0];
    float shtHumidity = shtReadings[1];

    Serial.print("SHT - Temperature: ");
    Serial.print(shtCelsius);
    Serial.print("°C");
    Serial.print("\tHumidity: ");
    Serial.print(shtHumidity);
    Serial.println("%");
}

void loop() {}
