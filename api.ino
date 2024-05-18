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

    Serial.println("POST " + url);

    WiFiClient client;
    HTTPClient http;

    // Your IP address with path or Domain name with URL path 
    http.begin(client, url);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"value\":20.5}");

    if (httpResponseCode>0) {
        Serial.println("Sent successfully");
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}
