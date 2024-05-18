double getRemoteTime() {
    String path = "/health/getRemoteTime";
    String url = "http://" + String(host) + path;

    JsonDocument remoteTimeResponse = httpGETRequest(url);
    double remoteTime = remoteTimeResponse["time"];

    return remoteTime;
}

void postSensorData() {
    String path = "/homeTracker/upload";
    String url = "http://" + String(host) + path;

    JsonDocument doc;
    doc["value"] = millis();

    httpPOSTRequest(url, doc);
}
