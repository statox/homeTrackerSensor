/*************************************************** 
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/

#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

bool initSHT31() {
    if (!sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
        Serial.println("Couldn't find SHT31");
        return false;
    }

    Serial.print("SHT31 found. Heater Enabled State: ");
    if (sht31.isHeaterEnabled()) {
        Serial.println("ENABLED");
    } else {
        Serial.println("DISABLED");
    }
    return true;
}

float* readSHT31() {
    float* result = new float[4];
    result[0] = 1;

    if (!initSHT31()) {
        return result;
    }

    float temperature = sht31.readTemperature();
    float humidity = sht31.readHumidity();

    result[0] = 0;
    result[1] = temperature;
    result[2] = humidity;

    // TODO Check if it is interesting to enable the heater in winter
    // to evaporate condensation
    // An ~3.0 degC temperature increase can be noted when heater is enabled
    // sht31.heater(true);

    return result;
}
