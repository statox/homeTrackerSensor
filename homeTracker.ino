#include "arduino_secrets.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* sensorName = "dev-sensor";

const unsigned long oneMinute = 60e6;
const unsigned long loopDelay = 10 * oneMinute;

void sleep () {
    Serial.println();
    Serial.println("Going to sleep");
    ESP.deepSleep(loopDelay);
}

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
    Serial.print("Battery: ");
    Serial.print(batteryPercent);
    Serial.print("% - ");
    Serial.print(batteryCharge);
    Serial.println("V");

    float* dhtReadings = readDHT();
    float dhtCelsius = dhtReadings[0];
    float dhtHumidity = dhtReadings[1];

    Serial.print("DHT - Temperature: ");
    Serial.print(dhtCelsius);
    Serial.print("°C");
    Serial.print("\t\tHumidity: ");
    Serial.print(dhtHumidity);
    Serial.println("%");

    float* bmeReadings = readBME280();
    float bmeCelsius = bmeReadings[0];
    float bmeHumidity = bmeReadings[1];
    float bmePres = bmeReadings[2];

    Serial.print("BME - Temp: ");
    Serial.print(bmeCelsius);
    Serial.print("°C");
    Serial.print("\t\tHumidity: ");
    Serial.print(bmeHumidity);
    Serial.print("% RH");
    Serial.print("\t\tPressure: ");
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
