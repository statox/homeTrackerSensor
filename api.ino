double getRemoteTime() {
    String path = "/health/getRemoteTime";
    String url = "http://" + String(host) + path;

    JsonDocument remoteTimeResponse = httpGETRequest(url);
    double remoteTime = remoteTimeResponse["time"];

    return remoteTime;
}

void postSensorData(String sensorName, double ts, float tempCelsius) {
    String path = "/homeTracker/upload";
    String url = "http://" + String(host) + path;

    JsonDocument doc;
    doc["sensorName"] = sensorName;
    doc["ts"] = ts;
    doc["tempCelsius"] = tempCelsius;

    httpPOSTRequest(url, doc);
}
