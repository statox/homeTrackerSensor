#include <ArduinoJson.h>
#include "config.h"
#include "BatteryManager.h"
#include "Statox_Api.h"
#include "Statox_Blink.h"
#include "Statox_Sensors.h"

BatteryManager batteryManager(A7);

void setup() {
    Serial.begin(9600);
    while(!Serial && millis() < 1000) {}
    batteryManager.initializeData();
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

    blink(1, 500, 500);

    ApiData apiData = {};
    apiData.sensorName = CONFIG_SENSOR_NAME;

    batteryManager.updateData();

    if (batteryManager.mustShutdown()) {
        // Trigger deepsleep without timeout to try avoiding depleting the battery
        shutdown();
    }
    blink(1, 500, 500);

    apiData.batteryCharge = batteryManager.batteryData.charge;
    apiData.batteryPercent = batteryManager.batteryData.percent;

#if defined(MAIN_SENSOR_BME)
    float* sensorReadings = readBME280();
#elif defined(MAIN_SENSOR_DHT)
    float* sensorReadings = readDHT();
#elif defined(MAIN_SENSOR_SHT)
    float* sensorReadings = readSHT31();
#endif

    blink(1, 500, 500);

    apiData.tempCelsius = sensorReadings[0];
    apiData.humidity = sensorReadings[1];
#ifdef MAIN_SENSOR_BME
    apiData.pressurePa = sensorReadings[2];
#endif

#ifdef HAS_INTERNAL_SENSOR
    float* internalSensorReadings = readDHT();
    apiData.internalTempCelsius = internalSensorReadings[0];
    apiData.internalHumidity = internalSensorReadings[1];
    blink(1, 500, 500);
#endif

    postSensorData(apiData);
    blink(2, 100, 100);
    sleep();
}
