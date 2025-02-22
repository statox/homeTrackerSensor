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
#include "config.h"

// TODO Validate the macro definition check
// 03/02/25: I wrote these checks, it compiles but I didn't test both
// branches on an actual board
#if defined(DHTTYPE) && defined(DHTPIN)
    // Initialize DHT sensor for normal 16mhz Arduino
    DHT dht(DHTPIN, DHTTYPE);

    void initDHT() { dht.begin(); }

    float* readDHT() {
        initDHT();

        // Reading temperature or humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        float h = dht.readHumidity();
        // Read temperature as Celsius
        float t = dht.readTemperature();

        float* result = new float[3];
        result[1] = t;
        result[2] = h;

        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t)) {
            result[0] = 1;
            Serial.println("Failed to read from DHT sensor!");
            return result;
        }
        result[0] = 0;

        return result;
    }
#else
    float* readDHT() {
        Serial.println("ERROR: Calling readDHT without DHTTYPE or DHTPIN defined");
        return new float[3];
    }
#endif
