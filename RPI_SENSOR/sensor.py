# /// script
# requires-python = ">=3.12"
# dependencies = [
#     "pyserial",
#     "requests<3",
# ]
# ///

import configparser
import datetime
import requests
import serial
import time

config = configparser.ConfigParser()
config.read("config.ini")

# Configuration
COM_PORT = config["usb"]["com_port"]
baud_rate = 115200
io_delay = 5

API_HOST = config["api"]["host"]
API_KEY = config["api"]["key"]

SENSOR_NAME = config["sensor"]["name"]


def read_sensor_data(ser):
    try:
        line = ser.readline().decode("utf-8").strip()
        serial, temperature, humidity, touch = line.split(", ")
        return float(temperature), float(humidity)
    except Exception as e:
        print("Error in read_sensor_data")
        print(e)
        return None, None


def send_data_to_api(temp: float, humidity: float):
    body = {"sensorName": SENSOR_NAME, "tempCelsius": temp, "humidity": humidity}
    headers = {"authorization": f"Bearer {API_KEY}"}
    x = requests.post(API_HOST, json=body, headers=headers)
    print("Response:", x.text)


def main():
    with serial.Serial(COM_PORT, baud_rate, timeout=1) as ser:
        while True:
            print("== ", datetime.datetime.now())
            temp, humidity = read_sensor_data(ser)
            print(f"Read, {temp}*C {humidity}%")
            send_data_to_api(temp, humidity)
            time.sleep(10 * 60)


if __name__ == "__main__":
    main()
