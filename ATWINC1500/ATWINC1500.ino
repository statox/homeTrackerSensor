#include "arduino_secrets.h"
#include <ArduinoJson.h>
#include "Statox_Sensors.h"
#include "Statox_Blink.h"

#include <SPI.h>
#include <WiFi101.h>

const char* sensorName = "dev-sensor-3";


int status = WL_IDLE_STATUS;
WiFiClient client;

void setup() {
    Serial.begin(9600);
    while(!Serial) { }

    initBlink();
    blink(10, 100, 100);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("===== Restart ======");
    Serial.println();

    if (!initWifi()) {
        Serial.println("WIFI FAILED STOPPING");
        return;
    }

    // // if there are incoming bytes available
    // // from the server, read them and print them:
    // while (client.available()) {
    //     char c = client.read();
    //     Serial.write(c);
    // }

    // // if the server's disconnected, stop the client:
    // if (!client.connected()) {
    //     Serial.println();
    //     Serial.println("disconnecting from server.");
    //     client.stop();
    // }

    Serial.println();
    blink(2, 500, 500);

    initSHT31();
    float* shtReadings = readSHT31();
    float shtCelsius = shtReadings[0];
    float shtHumidity = shtReadings[1];

    Serial.print("SHT - Temperature: ");
    Serial.print(shtCelsius);
    Serial.print("°C");
    Serial.print("\tHumidity: ");
    Serial.print(shtHumidity);
    Serial.println("%");
}

void loop() {}
