#include "secrets.h"
#include "config.h"
#include <ArduinoJson.h>
#include "Statox_Sensors.h"
#include "Statox_Blink.h"

typedef struct {
    char* sensorName;

    float tempCelsius;
    float humidity;
    float pressurePa;

    float internalTempCelsius;
    float internalHumidity;

    float batteryCharge;
    float batteryPercent;
} ApiData;

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
}

void loop() {
    if (!initWifi()) {
        sleep();
        return;
    }

    initSHT31();

    Serial.println();
    blink(2, 500, 500);

    ApiData apiData = {};
    apiData.sensorName = CONFIG_SENSOR_NAME;

    float* batteryData = readBatteryLevel();
    apiData.batteryCharge = batteryData[0];
    apiData.batteryPercent = batteryData[1];

    float* sensorReadings = readSHT31();
    apiData.tempCelsius = sensorReadings[0];
    apiData.humidity = sensorReadings[1];
    #ifdef HAS_PRESSURE_SENSOR
    apiData.pressurePa = sensorReadings[2];
    #endif

    #ifdef HAS_INTERNAL_SENSOR
    float* internalSensorReadings = readDHT();
    apiData.internalTempCelsius = internalSensorReadings[0];
    apiData.internalHumidity = internalSensorReadings[1];
    #endif

    postSensorData(apiData);
    sleep();
}
