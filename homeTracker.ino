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
    delay(5 * 1000);
    Serial.begin(9600);

    // Needed for blink
    pinMode(0, OUTPUT);

    blink(10, 100, 100);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("===== Restart ======");
    Serial.println();

    connectToSSID(ssid, password);
}

void loop() {
    Serial.println();
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
    delay(30 * 1000);
}
