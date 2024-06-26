#include "secrets.h"
#include "config.h"
#include <ArduinoJson.h>
#include "Statox_Sensors.h"
#include "Statox_Blink.h"

const char* sensorName = "dev-sensor";

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

    if (!initWifi()) {
        sleep();
        return;
    }

    initDHT();
    initBME280();

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

    float* dhtReadings = readDHT();
    float dhtCelsius = dhtReadings[0];
    float dhtHumidity = dhtReadings[1];

    Serial.print("DHT - Temperature: ");
    Serial.print(dhtCelsius);
    Serial.print("°C");
    Serial.print("\tHumidity: ");
    Serial.print(dhtHumidity);
    Serial.println("%");

    float* bmeReadings = readBME280();
    float bmeCelsius = bmeReadings[0];
    float bmeHumidity = bmeReadings[1];
    float bmePres = bmeReadings[2];

    Serial.print("BME - Temperature: ");
    Serial.print(bmeCelsius);
    Serial.print("°C");
    Serial.print("\tHumidity: ");
    Serial.print(bmeHumidity);
    Serial.print("%");
    Serial.print("\tPressure: ");
    Serial.print(bmePres);
    Serial.println("Pa");

    postSensorData(
        sensorName,

        dhtCelsius,
        dhtHumidity,

        bmeCelsius,
        bmeHumidity,
        bmePres,

        batteryCharge,
        batteryPercent
    );
    sleep();
}

void loop() {}
