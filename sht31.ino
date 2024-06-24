/*************************************************** 
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void initSHT31() {
    while(!sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
        Serial.println("Couldn't find SHT31");
        delay(1000);
    }

    Serial.print("SHT31 found. Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
        Serial.println("ENABLED");
    else
        Serial.println("DISABLED");
}


float* readSHT31() {
    float temperature = sht31.readTemperature();
    float humidity = sht31.readHumidity();

    float* result = new float[3];
    result[0] = temperature;
    result[1] = humidity;

    return result;
    // TODO Check if it is interesting to enable the heater in winter
    // to evaporate condensation
    // An ~3.0 degC temperature increase can be noted when heater is enabled
    // sht31.heater(true);
}
