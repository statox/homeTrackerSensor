int getRemoteTime() {
    String path = "/health/getRemoteTime";
    String url = "http://" + String(host) + path;

    String remoteTimeResponse = httpGETRequest(url);
    JSONVar parsedRemoteTimeResponse = JSON.parse(remoteTimeResponse);
    int remoteTime = parsedRemoteTimeResponse["time"];

    return remoteTime;
}

void postSensorData() {
    String path = "/homeTracker/upload";
    String url = "http://" + String(host) + path;

    JsonDocument doc;
    doc["value"] = millis();

    httpPOSTRequest(url, doc);
}
