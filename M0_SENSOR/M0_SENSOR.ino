#include <ArduinoJson.h>
#include "config.h"
#include "BatteryManager.h"
#include "BoardWatcher.h"
#include "Statox_Api.h"
#include "Statox_Blink.h"
#include "Statox_Sensors.h"

// Loop should take ~7s so 30s gives some margin for a slow wifi
BoardWatcher boardWatcher(30 * 1000);
BatteryManager batteryManager(A7);

bool detectedForcedReset = false;;
void TC3_Handler() {
    boardWatcher.timerCallback();
}

void setup() {
    Serial.begin(9600);
    while(!Serial && millis() < 1000) {}
    boardWatcher.init();
    batteryManager.initializeData();

    if (PM->RCAUSE.bit.SYST == 1) {
        detectedForcedReset = true;
    }
}

void loop() {
    boardWatcher.newLoop();

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

    apiData.timeToSendMs = boardWatcher.currentLoopTime();
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
