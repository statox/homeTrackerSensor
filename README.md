# Resources

- https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/
- https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/pinouts
    - https://learn.adafruit.com/assets/46249

# Libraries

- [ArduinoJson](https://arduinojson.org) Used in api code for GET and POST requests
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) (Its dependency "Adafruit Unified Sensor" is automatically installed by Arduino IDE when installing the lib) Used to read from the DHT11 sensor
- [BME280 Library 3.0.0 by Tyler Glenn](https://github.com/finitespace/BME280) Used to read from the BME280 sensor. I tried used the Adafruit library for the BME280 but it doesn't work with the sensor I bought from Velleman (whadda.com). I don't know if there is compability issue between the breakout boards and libraries.
