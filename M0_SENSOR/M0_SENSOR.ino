#include <ArduinoJson.h>
#include "config.h"
#include "BatteryManager.h"
#include "Statox_Api.h"
#include "Statox_Blink.h"
#include "Statox_Sensors.h"

BatteryManager batteryManager(A7);

bool detectedForcedReset = false;;

void setup() {
    Serial.begin(9600);
    while(!Serial && millis() < 1000) {}
    batteryManager.initializeData();

    if (PM->RCAUSE.bit.SYST == 1) {
        detectedForcedReset = true;
    }
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
    bool lowBattery = batteryManager.mustShutdown();
    if (lowBattery) {
        apiData.detectedLowBattery = lowBattery;
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

    if (sensorReadings[0] == 0) {
        apiData.tempCelsius = sensorReadings[1];
        apiData.humidity = sensorReadings[2];
    } else {
        apiData.detectedSensorFailure = true;
    }
#ifdef MAIN_SENSOR_BME
    if (sensorReadings[0] == 0) {
        apiData.pressurePa = sensorReadings[3];
    }
#endif

#ifdef HAS_INTERNAL_SENSOR
    float* internalSensorReadings = readDHT();
    if (internalSensorReadings[0] == 0) {
        apiData.internalTempCelsius = internalSensorReadings[1];
        apiData.internalHumidity = internalSensorReadings[2];
    } else {
        apiData.detectedInternalSensorFailure = true;
    }
    blink(1, 500, 500);
#endif

    apiData.detectedForcedReset = detectedForcedReset;
    postSensorData(apiData);
    blink(2, 100, 100);

    detectedForcedReset = false;

    if (lowBattery) {
        // Trigger deepsleep without timeout to try avoiding depleting the battery
        shutdown();
    }

    sleep();
}
