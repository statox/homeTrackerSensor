# /// script
# requires-python = ">=3.12"
# dependencies = [
#     "pyserial",
#     "requests<3",
# ]
# ///

import requests
import serial
import time

# Configuration
com_port = "/dev/ttyACM0"  # Adjust this to your COM port
baud_rate = 115200
io_delay = 5

API_HOST = "http://api.statox.fr/homeTracker/upload"
API_KEY = "CHANGEME"


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
    body = {"sensorName": "colonne", "tempCelsius": temp, "humidity": humidity}
    headers = {"authorization": f"Bearer {API_KEY}"}
    x = requests.post(API_HOST, json=body, headers=headers)
    print("Response:", x.text)


def main():
    with serial.Serial(com_port, baud_rate, timeout=1) as ser:
        while True:
            temp, humidity = read_sensor_data(ser)
            print(f"Read, {temp}*C {humidity}%")
            send_data_to_api(temp, humidity)
            time.sleep(10 * 60)


if __name__ == "__main__":
    main()
