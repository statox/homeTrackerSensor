#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <ArduinoJson.h>

const char* ssid     = "CHANGEME";
const char* password = "CHANGEME";

const char* host = "api.statox.fr";

void blink(int times, int length, int interval) {
    Serial.print("Blink");

    for (int i=0; i<times; i++) {
        Serial.print(".");
        digitalWrite(0, LOW);
        delay(length);
        digitalWrite(0, HIGH);
        delay(interval);
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    pinMode(0, OUTPUT);

    blink(10, 100, 100);
    delay(10000);
    blink(5, 800, 100);

    // We start by connecting to a WiFi network
    connectToSSID(ssid, password);
}

void loop() {
    delay(10000);
    blink(2, 500, 500);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    double remoteTime = getRemoteTime();

    Serial.print("Remote time: ");
    Serial.println(remoteTime);

    postSensorData();

    Serial.println();
}
