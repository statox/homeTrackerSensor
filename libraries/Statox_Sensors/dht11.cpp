/*
 * Code for the DHT11 temperature and humidity sensor using the
 * adafruit DHT sensor library https://github.com/adafruit/DHT-sensor-library
 *
 * Schematics are basics 3.3V and FND from ESP8266 to Vin and GND of DHT11
 *  (The sensor works well with 3.3V logic)
 * Data pin of DHT11 to ESP8266 GPIO2
 *
 * IMPORTANT Can't read the sensor more than ~once a second
 */

#include "DHT.h"

// TODO: Extract the define to main code
#define DHTPIN 13      // Pin used to read the DHT sensor
#define DHTTYPE DHT22  // Can be changed for DHT11 sensors (I don't use DHT11 anymore because the accuracy isn't good enough)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void initDHT() {
    dht.begin();
}

float* readDHT() {
    initDHT();

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();

    float* result = new float[2];
    result[0] = t;
    result[1] = h;


    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
    }

    // TODO Check what is "heat index"
    // Compute heat index
    // Must send in temp in Fahrenheit!
    // float f = dht.readTemperature(true);
    // float hi = dht.computeHeatIndex(f, h);

    return result;
}
