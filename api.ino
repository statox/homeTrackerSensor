double getRemoteTime() {
    String path = "/health/getRemoteTime";
    String url = "http://" + String(host) + path;

    JsonDocument remoteTimeResponse = httpGETRequest(url);
    double remoteTime = remoteTimeResponse["time"];

    return remoteTime;
}

void postSensorData(
    String sensorName,
    double ts,
    float tempCelsius,
    float tempCelsius2,
    float humidity
) {
    String path = "/homeTracker/upload";
    String url = "http://" + String(host) + path;

    JsonDocument doc;
    doc["sensorName"] = sensorName;
    doc["ts"] = ts;
    doc["tempCelsius"] = tempCelsius;
    doc["tempCelsius2"] = tempCelsius2;
    doc["humidity"] = humidity;

    httpPOSTRequest(url, doc);
}
