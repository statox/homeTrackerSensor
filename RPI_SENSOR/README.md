# SHT41 Trinkey + Rpi

WORK IN PROGRESS.

This is project is about leveraging a [SHT4X trinkey by Adafruit](https://learn.adafruit.com/adafruit-sht4x-trinkey) to report temperature and humidity.

The idea is to have

- The default program running on the Trinkey which writes on the serial port an id, the temperature, humidity and value of the capacitive sensor.
- The python script running on the rpi which regularly reads from the serial port and calls my API to report the read values.

Lots of to dos:

- Add the Trinkey program to this repo, maybe rework it to only output necessary data.
- Better package the python script. For now it is copied on the rpi and running in a `screen` session started with `uv run sensor.py` we can do better.
