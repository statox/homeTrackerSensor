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
    float humidity,
    int batteryReading,
    int batteryPercent
) {
    String path = "/homeTracker/upload";
    String url = "http://" + String(host) + path;

    JsonDocument doc;
    doc["sensorName"] = sensorName;
    doc["ts"] = ts;
    doc["tempCelsius"] = tempCelsius;
    doc["humidity"] = humidity;
    doc["batteryReading"] = batteryReading;
    doc["batteryPercent"] = batteryPercent;

    httpPOSTRequest(url, doc);
}
