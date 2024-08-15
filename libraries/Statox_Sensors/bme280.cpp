#include <BME280I2C.h>
#include <Wire.h>

// Default : forced mode, standby time = 1000 ms
// Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,
BME280I2C bme;

bool initBME280() {
    Wire.begin();
    if(!bme.begin()) {
        Serial.println("Could not find BME280 sensor!");
        return false;
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

    return true;
}

float* readBME280() {
    float* result = new float[4];
    result[0] = 1;

    if (!initBME280()) {
        return result;
    }
    result[0] = 0;

    float temperature(NAN), humidity(NAN), pressure(NAN);
    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
    BME280::PresUnit presUnit(BME280::PresUnit_Pa);

    bme.read(pressure, temperature, humidity, tempUnit, presUnit);

    result[1] = temperature;
    result[2] = humidity;
    result[3] = pressure;

    return result;
}
