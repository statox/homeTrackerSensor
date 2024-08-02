void postSensorData(ApiData apiData) {
    String path = "/homeTracker/upload";
    String url = "http://" + String(CONFIG_API_HOSTNAME) + path;

    JsonDocument doc;
    doc["sensorName"] = apiData.sensorName;

    doc["tempCelsius"] = apiData.tempCelsius;
    doc["humidity"] = apiData.humidity;

    #ifdef MAIN_SENSOR_BME
    doc["pressurePa"] = apiData.pressurePa;
    #endif

    #ifdef HAS_INTERNAL_SENSOR
    doc["internalTempCelsius"] = apiData.internalTempCelsius;
    doc["internalHumidity"] = apiData.internalHumidity;
    #endif

    doc["batteryCharge"] = apiData.batteryCharge;
    doc["batteryPercent"] = apiData.batteryPercent;

    doc["timeToSendMs"] = apiData.timeToSendMs;
    doc["detectedLowBattery"] = apiData.detectedLowBattery;
    doc["detectedForcedReset"] = apiData.detectedForcedReset;

    httpPOSTRequest(url, doc);
}
