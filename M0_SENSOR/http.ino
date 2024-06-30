#include <ArduinoHttpClient.h>
#include <WiFi101.h>

// Expecting complete URL http://host/path
JsonDocument httpGETRequest(String url) {
    Serial.println("GET " + url);

    WiFiClient client;
    HttpClient http = HttpClient(client, CONFIG_API_HOSTNAME, 80);

    http.get(url);

    int httpResponseCode = http.responseStatusCode();
    JsonDocument response;

    if (httpResponseCode<=0) {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);

        return response;
    }

    DeserializationError error = deserializeJson(response, http.responseBody());

    // Test if parsing succeeds.
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());

        return response;
    }

    return response;
}

void httpPOSTRequest(String url, JsonDocument payload) {
    String payloadStr;
    serializeJson(payload, payloadStr);

    Serial.println("POST " + url);
    serializeJson(payload, Serial);

    WiFiClient client;
    HttpClient http = HttpClient(client, CONFIG_API_HOSTNAME, 80);

    String contentType = "application/json";
    http.post(url, contentType, payloadStr);

    int httpResponseCode = http.responseStatusCode();

    if (httpResponseCode<=0) {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
}
