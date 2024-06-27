#include <BME280I2C.h>
#include <Wire.h>

// Default : forced mode, standby time = 1000 ms
// Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,
BME280I2C bme;

void initBME280() {
    Wire.begin();
    if(!bme.begin()) {
        Serial.println("Could not find BME280 sensor!");
        return;
    }

    switch(bme.chipModel()) {
        case BME280::ChipModel_BME280:
            Serial.println("Found BME280 sensor! Success.");
            break;
        case BME280::ChipModel_BMP280:
            Serial.println("Found BMP280 sensor! No Humidity available.");
            break;
        default:
            Serial.println("Found UNKNOWN sensor! Error!");
    }
}

float* readBME280() {
    initBME280();

    float temperature(NAN), humidity(NAN), pressure(NAN);

    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
    BME280::PresUnit presUnit(BME280::PresUnit_Pa);

    bme.read(pressure, temperature, humidity, tempUnit, presUnit);

    float* result = new float[3];
    result[0] = temperature;
    result[1] = humidity;
    result[2] = pressure;

    return result;
}
