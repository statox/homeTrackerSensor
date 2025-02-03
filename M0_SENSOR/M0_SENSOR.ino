#include "BatteryManager.h"
#include "Statox_Api.h"
#include "Statox_Blink.h"
#include "Statox_Sensors.h"
#include "config.h"
#include <Adafruit_SleepyDog.h>
#include <ArduinoJson.h>

BatteryManager batteryManager(A7);

bool detectedForcedReset = false;

void setup() {
    Serial.begin(9600);
    while (!Serial && millis() < 1000) {}
    batteryManager.initializeData();

    if (Watchdog.resetCause() == 32) {
        detectedForcedReset = true;
    }
}

void loop() {
    initBlink();
    blink(5, 100, 100);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("===== Restart ======");
    Serial.print("sensor name:");
    Serial.println(CONFIG_SENSOR_NAME);
    Serial.println();

    // Watchdog provided by the SleepyDog library
    // Giving it 10 seconds setups a max time before reset of about 8s (not sure why)
    // which should be enough: A Loop lasts ~7 seconds and we reset the watchdog
    // several times during the loop.
    // If one operation loops for too long the watchdog will trigger a reset of the board.
    // IMPORTANT: Make sure to disable the watchdog before sleep or shutdown otherwise it
    // will reset the board during the sleep
    // IMPORTANT 2: When setting up a sensor for the first time (or when the box restarts)
    // the WiFi initialization takes a bit longer than 10 seconds.
    //     - We tried enabling the watchdog after connecting to WiFi but the board sometimes
    //       hands on WiFi connection even without the box restarting.
    //     - The M0 doesn't have an EEPROM so we can't store data persistent between the reboots
    //       So we can't disable the watchdog if we failed on WiFi several times
    //     - The longest watchdog delay we manage to set on the M0 is ~16 seconds. For now
    //       we try using this but it's likely too short to handle slow WiFi init.
    //
    // So for now I'm not sure how to solve the problem
    // TODO Maybe The WiFi library can give a status of whether the connection happened before
    // and if it didn't then we can try disabling the watchdog because we are in a first setup?
    // Does that really works if the box restarts after a successful connection?
    Watchdog.enable(16000);

    if (!initWifi()) {
        Watchdog.disable(); // Is not useful since watchdog is not enabled yet
        sleep();
        return;
    }

    Watchdog.reset();
    blink(1, 100, 100);

    ApiData apiData = {};
    apiData.sensorName = CONFIG_SENSOR_NAME;

    // This should probably happen before anything else so that we can shutdown the board
    // when we have a really low battery
    batteryManager.updateData();
    bool lowBattery = batteryManager.mustShutdown();
    if (lowBattery) {
        apiData.detectedLowBattery = lowBattery;
    }
    Watchdog.reset();
    blink(1, 100, 100);

    apiData.batteryCharge = batteryManager.batteryData.charge;
    apiData.batteryPercent = batteryManager.batteryData.percent;

#if defined(MAIN_SENSOR_BME)
    float* sensorReadings = readBME280();
#elif defined(MAIN_SENSOR_DHT)
    float* sensorReadings = readDHT();
#elif defined(MAIN_SENSOR_SHT)
    float* sensorReadings = readSHT31();
#endif

    Watchdog.reset();
    blink(1, 100, 100);

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
    Watchdog.reset();
    blink(1, 100, 100);
#endif

    apiData.detectedForcedReset = detectedForcedReset;
    JsonDocument res = postSensorData(apiData);
    int sleepTime = res["instructSleepSec"];
    Watchdog.reset();
    blink(2, 50, 50);

    detectedForcedReset = false;

    if (lowBattery) {
        // Trigger deepsleep without timeout to try avoiding depleting the battery
        Watchdog.disable();
        shutdown();
    }

    Watchdog.disable();
    sleep(sleepTime);
}
