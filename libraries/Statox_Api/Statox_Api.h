typedef struct {
    String sensorName;

    float tempCelsius;
    float humidity;
    float pressurePa;

    float internalTempCelsius;
    float internalHumidity;

    float batteryCharge;
    float batteryPercent;

    int timeToSendMs;
    bool detectedLowBattery;
    bool detectedForcedReset;
} ApiData;

void postSensorData(ApiData apiData);
