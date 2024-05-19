#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "CHANGEME";
const char* password = "CHANGEME";

const char* host = "api.statox.fr";

const char* sensorName = "dev-sensor";

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

    // connectToSSID(ssid, password);
    initDHT();
}

void loop() {
    Serial.println();
    blink(2, 500, 500);

    /*
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    double remoteTime = getRemoteTime();
    postSensorData(sensorName, remoteTime, celsius);
    */

    const double vmaCelsius = readTempCelsius();

    float* dhtReadings = readDHT();
    float dhtCelsius = dhtReadings[0];
    float dhtHumidity = dhtReadings[1];

    Serial.print("VMA320: ");
    Serial.print(vmaCelsius);
    Serial.print("(C) DHT: ");
    Serial.print(dhtCelsius);
    Serial.print("(C)  Hum: ");
    Serial.println(dhtHumidity);

    Serial.println();
    delay(5 * 1000);
}
