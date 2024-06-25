#include "arduino_secrets.h"
#include <ArduinoJson.h>
#include "Statox_Sensors.h"
#include "Statox_Blink.h"

const char* sensorName = "dev-sensor-3";

void setup() {
    Serial.begin(9600);
    // Add a safe guard of 10 seconds because when starting unplugged from USB
    // Serial will never be available. TODO Find out why its not needed on ESP8266
    while(!Serial && millis() < 5000) {}

    initBlink();
    blink(10, 100, 100);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("===== Restart ======");
    Serial.println();

    initSleep();
}

void loop() {
    if (!initWifi()) {
        Serial.println("WIFI FAILED STOPPING");
        sleep();
        return;
    }

    initSHT31();

    Serial.println();
    blink(2, 500, 500);

    float* batteryData = readBatteryLevel();
    float batteryCharge = batteryData[0];
    float batteryPercent = batteryData[1];
    float batteryReading = batteryData[2];
    Serial.print("Battery - Charge: ");
    Serial.print(batteryPercent);
    Serial.print("%");
    Serial.print("\tVoltage:");
    Serial.print(batteryCharge);
    Serial.print("V");
    Serial.print("\tAnalog reading: ");
    Serial.println(batteryReading);

    float* shtReadings = readSHT31();
    float shtCelsius = shtReadings[0];
    float shtHumidity = shtReadings[1];

    Serial.print("SHT - Temperature: ");
    Serial.print(shtCelsius);
    Serial.print("°C");
    Serial.print("\tHumidity: ");
    Serial.print(shtHumidity);
    Serial.println("%");

    postSensorData(
        sensorName,

        shtCelsius,
        shtHumidity,

        batteryCharge,
        batteryPercent
    );
    sleep();
}
