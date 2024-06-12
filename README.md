# Resources

- https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/
- https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/pinouts
    - https://learn.adafruit.com/assets/46249

# Libraries

- [ArduinoJson](https://arduinojson.org) Used in api code for GET and POST requests
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) (Its dependency "Adafruit Unified Sensor" is automatically installed by Arduino IDE when installing the lib) Used to read from the DHT11 sensor
- [BME280 Library 3.0.0 by Tyler Glenn](https://github.com/finitespace/BME280) Used to read from the BME280 sensor. I tried used the Adafruit library for the BME280 but it doesn't work with the sensor I bought from Velleman (whadda.com). I don't know if there is compability issue between the breakout boards and libraries.

# Components

## Main board: ESP8266 [Adafruit Feather Huzzah](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266)

The ESP8266 supports a deep sleep mode which allows for very low current consumption while it is not active, it can read the DHT22 on a digital pin and the BME280 via I2C.
The main drawback is that the board doesn't support SSL and HTTPS properly. In the future I'll probably want to switch to an ESP32.


## Sensor: DHT22 [Whadda Temperature and humidity sensor](https://whadda.com/product/cm2302-dht22-temperature-humidity-sensor-module-wpse345/)

Humidity: 0-100% (accuracy 2-5%)
Temperature: -40 to 80°C (accuracy 0.5°C)
Power: 3-5V
Current: 2.5mA max current use during conversion (while requesting data)
Sampling: No more than 0.5 Hz sampling rate (once every 2 seconds)

## Sensor: BME280 [Whadda Temperature, humidity and pressure sensor](https://whadda.com/product/bme280-temperature-humidity-and-pressure-sensor-wpse335/)

Humidity: 0-100% (accuracy 3%)
Temperature: -40 to 85°C (accuracy 1°C)
Pressure: Not sure about range (accuracy 1hPa)
Power: 1.71-3.6V
Current: 3.6 uA @ 1Hz for humidity, temperature and pressure reading
Sampling: 1 Hz sampling rate (once every seconds)

[Bosch datasheet](https://www.mouser.com/datasheet/2/783/BST-BME280-DS002-1509607.pdf)

# How it works

TODO: Add proper explanations and schematics.

General principle:

- Don't use a loop, instead do everything in `setup()` function and then use `ESP.deepSleep` to avoid battery consumption.
- Initialize Wifi and check that the connection is working, if not go to sleep and try again later
- Initialize the sensors
- Do the readings, each sensor has its own file and a `read` function which return the different values in an array of `float`
- Pass the read values to a api function which will be reponsible for creating a JSON document and post it to the api.
- Go to deep sleep and repeat.

The configurations are in a dedicated header file to change the behavior easily from a central place (TODO move the sensor name there and implement a way to toggle which sensors to use)

Some of the objects I'm making are intended to have only a DHT22 (to make indoor measurements) and some are intended to live in a weatherproof enclosure with one DHT22 inside the enclosure (to make sure the board and battery remain in a safe setting) and one BME280 outside of the enclosure of environmental measurements.
