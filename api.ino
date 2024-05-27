// Kept for an example of a get request
double getRemoteTime() {
    String path = "/health/getRemoteTime";
    String url = "http://" + String(host) + path;

    JsonDocument remoteTimeResponse = httpGETRequest(url);
    double remoteTime = remoteTimeResponse["time"];

    return remoteTime;
}

void postSensorData(
    String sensorName,
    float tempCelsius,
    float humidity,
    float batteryCharge,
    float batteryPercent
) {
    String path = "/homeTracker/upload";
    String url = "http://" + String(host) + path;

    JsonDocument doc;
    doc["sensorName"] = sensorName;
    doc["tempCelsius"] = tempCelsius;
    doc["humidity"] = humidity;
    doc["batteryCharge"] = batteryCharge;
    doc["batteryPercent"] = batteryPercent;

    httpPOSTRequest(url, doc);
}
