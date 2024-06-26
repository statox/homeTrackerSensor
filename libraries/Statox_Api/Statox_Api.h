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

void postSensorData(ApiData apiData);
