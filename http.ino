// Expecting complete URL http://host/path
String httpGETRequest(String url) {
    Serial.println("GET " + url);

    WiFiClient client;
    HTTPClient http;

    // Your IP address with path or Domain name with URL path 
    http.begin(client, url);

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String payload = "{}"; 

    if (httpResponseCode>0) {
        payload = http.getString();
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    return payload;
}

void httpPOSTRequest(String url, JsonDocument payload) {
    String payloadStr;
    serializeJson(payload, payloadStr);

    Serial.println("POST " + url);
    serializeJson(payload, Serial);

    WiFiClient client;
    HTTPClient http;

    // Your IP address with path or Domain name with URL path
    http.begin(client, url);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payloadStr);

    if (httpResponseCode<=0) {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
