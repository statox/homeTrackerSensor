#include "secrets.h"
#include <SPI.h>
#include <WiFi101.h>

boolean connectToSSID(const char* ssid, const char* password) {
    Serial.print("Connecting to: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    const int maxTries = 30;
    int tries = 0;

    while (WiFi.status() != WL_CONNECTED && tries < maxTries) {
        tries++;
        delay(500);
        Serial.print("try ");
        Serial.print(tries);
        Serial.print(" status ");
        Serial.println(WiFi.status());
    }

    if (tries == maxTries) {
        Serial.println();
        Serial.println("WiFi not connected");
        return false;
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    return true;
}

boolean initWifi() {
    WiFi.setPins(8, 7, 4, 2);

    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        return false;
    }

    if (!connectToSSID(SECRET_WIFI_SSID, SECRET_WIFI_PASS)) {
        Serial.println("Connection to wifi failed");
        return false;
    }

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(CONFIG_API_HOSTNAME, httpPort)) {
        Serial.println("Connection to API failed");
        return false;
    }

    return true;
}
