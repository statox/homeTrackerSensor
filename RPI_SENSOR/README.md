# SHT41 Trinkey + Rpi

This is project is about leveraging a [SHT4X trinkey by Adafruit](https://learn.adafruit.com/adafruit-sht4x-trinkey) to report temperature and humidity using a raspberry instead of a microcontroller like with the [`M0_SENSOR`](../M0_SENSOR) directory

Two parts are needed:

- The SHT41 trinkey, running the original program shipped by Adafruit. This program writes on the serial port an id, the temperature, humidity, and value of the capacitive sensor.
- The raspberry running the python script which reads the data from USB and send it to the API.

## SHT41 Trinkey

TODO: Version the program in this repo and add process to upload the progam to the key. This is not something I have had the need to do yet as I'm using the factory program.

## Raspberry

- Clone this repo to the raspberry and navigate to the [`RPI_SENSOR`](./.) directory
- Edit the [`config.ini`](./config.ini) file to change the sensor name and setup the API key
- Run `sudo docker compose up -d --build`

The docker container is based on an image providing `uv` to run the script
