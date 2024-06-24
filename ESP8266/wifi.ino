#include <ESP8266WiFi.h>

void scanSSIDS() {
    Serial.println("Disconnecting ... ");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.print("Scan start ... ");
    int n = WiFi.scanNetworks();
    Serial.print(n);
    Serial.println(" network(s) found");
    for (int i = 0; i < n; i++) {
        Serial.println(WiFi.SSID(i));
    }
    Serial.println();
}

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
    if (!connectToSSID(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS)) {
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
