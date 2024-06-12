// Kept for an example of a get request
double getRemoteTime() {
    String path = "/health/getRemoteTime";
    String url = "http://" + String(CONFIG_API_HOSTNAME) + path;

    JsonDocument remoteTimeResponse = httpGETRequest(url);
    double remoteTime = remoteTimeResponse["time"];

    return remoteTime;
}

void postSensorData(
    String sensorName,

    float dhtCelsius,
    float dhtHumidity,

    float bmeCelsius,
    float bmeHumidity,
    float bmePres,

    float batteryCharge,
    float batteryPercent
) {
    String path = "/homeTracker/upload";
    String url = "http://" + String(CONFIG_API_HOSTNAME) + path;

    JsonDocument doc;
    doc["sensorName"] = sensorName;

    doc["tempCelsius"] = dhtCelsius;
    doc["humidity"] = dhtHumidity;

    doc["pressurePa"] = bmePres;
    doc["tempCelsius2"] = bmeCelsius;
    doc["humidity2"] = bmeHumidity;

    doc["batteryCharge"] = batteryCharge;
    doc["batteryPercent"] = batteryPercent;

    httpPOSTRequest(url, doc);
}
