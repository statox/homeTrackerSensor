#include "secrets.h"
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

    if (httpResponseCode <= 0) {
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

    http.beginRequest();
    http.post(url);
    http.sendHeader("Content-Type", contentType);
    http.sendHeader("Content-Length", payloadStr.length());
    http.sendHeader("authorization", SECRET_API_AUTH_HEADER);
    http.beginBody();
    http.print(payloadStr);
    http.endRequest();


    int httpResponseCode = http.responseStatusCode();

    if (httpResponseCode <= 0) {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
}

JsonDocument httpPOSTRequestWithResponseBody(String url, JsonDocument payload) {
    String payloadStr;
    serializeJson(payload, payloadStr);

    Serial.println("POST " + url);
    serializeJson(payload, Serial);

    WiFiClient client;
    HttpClient http = HttpClient(client, CONFIG_API_HOSTNAME, 80);

    String contentType = "application/json";

    http.beginRequest();
    http.post(url);
    http.sendHeader("Content-Type", contentType);
    http.sendHeader("Content-Length", payloadStr.length());
    http.sendHeader("authorization", SECRET_API_AUTH_HEADER);
    http.beginBody();
    http.print(payloadStr);
    http.endRequest();


    int httpResponseCode = http.responseStatusCode();

    JsonDocument response;

    if (httpResponseCode <= 0) {
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
