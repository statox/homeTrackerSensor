#include "secrets.h"
#include "config.h"
#include <ArduinoJson.h>
#include "Statox_Api.h"
#include "Statox_Blink.h"
#include "Statox_Sensors.h"

void setup() {
    Serial.begin(9600);
    while(!Serial && millis() < 5000) {}
}

void loop() {
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
