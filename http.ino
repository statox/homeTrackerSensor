#include <ESP8266HTTPClient.h>

// Expecting complete URL http://host/path
JsonDocument httpGETRequest(String url) {
    Serial.println("GET " + url);

    WiFiClient client;
    HTTPClient http;

    http.begin(client, url);

    int httpResponseCode = http.GET();
    JsonDocument response;

    if (httpResponseCode<=0) {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);

        http.end();
        return response;
    }

    DeserializationError error = deserializeJson(response, http.getString());

    // Test if parsing succeeds.
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());

        http.end();
        return response;
    }

    http.end();
    return response;
}

void httpPOSTRequest(String url, JsonDocument payload) {
    String payloadStr;
    serializeJson(payload, payloadStr);

    Serial.println("POST " + url);
    serializeJson(payload, Serial);

    WiFiClient client;
    HTTPClient http;

    http.begin(client, url);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payloadStr);

    if (httpResponseCode<=0) {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
