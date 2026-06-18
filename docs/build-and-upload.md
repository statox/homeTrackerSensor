# Building and uploading firmware from the terminal

> [!DANGER]
> Except for the "Serial Monitor" section nothing here have been tested. I generated that but ended up not needing it. Keeping it for next time

This project uses [`arduino-cli`](https://arduino.github.io/arduino-cli/) instead of the Arduino IDE to compile and flash firmware.

## Prerequisites

### arduino-cli

Install `arduino-cli` if not already present:

```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```

### Adafruit SAMD board package

The Adafruit SAMD board package must be installed. Check what is already installed:

```bash
arduino-cli core list
```

If `adafruit:samd` is missing, add the Adafruit board index URL and install:

```bash
arduino-cli config add board_manager.additional_urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
arduino-cli core update-index
arduino-cli core install adafruit:samd
```

## Process

### 1. Configure the sketch for the target sensor

All sensor-specific settings live in `libraries/Statox_Config/config.h`. Only one sensor block should be active at a time. Comment out the current block and uncomment the target sensor's block.

Example for the `jardiniere` sensor:

```c
/* Chambre */
// #define CONFIG_SENSOR_NAME "chambre"
// #define MAIN_SENSOR_DHT
// #define DHTTYPE DHT22

/* Jardiniere */
#define CONFIG_SENSOR_NAME "jardiniere"
#define MAIN_SENSOR_SHT
#define HAS_INTERNAL_SENSOR
#define DHTTYPE DHT11
```

The available sensor profiles are documented as commented blocks at the bottom of `config.sample.h`.

### 2. Connect the board and find its port

Plug the board in via USB, then run:

```bash
arduino-cli board list
```

The Feather M0 shows up as `adafruit:samd:adafruit_feather_m0`, typically on `/dev/ttyACM0`.

### 3. Compile

Run from the repo root:

```bash
arduino-cli compile \
  --fqbn adafruit:samd:adafruit_feather_m0 \
  --libraries /path/to/homeTrackerSensor/libraries \
  /path/to/homeTrackerSensor/M0_SENSOR
```

Replace `/path/to/homeTrackerSensor` with the actual path to your clone of this repo.

### 4. Upload

```bash
arduino-cli upload \
  --fqbn adafruit:samd:adafruit_feather_m0 \
  --port /dev/ttyACM0 \
  /path/to/homeTrackerSensor/M0_SENSOR
```

## Serial Monitor

Start this then connect the board

```
until [ -e /dev/ttyACM0 ]; do sleep 0.1; done && arduino-cli monitor --port /dev/ttyACM0 --config baudrate=9600
```

## Troubleshooting

### Board not detected or upload fails

If the board is stuck (e.g. caught in the watchdog reset loop) it may not enumerate properly over USB. Put it into bootloader mode manually by **double-tapping the reset button**. The onboard LED will pulse and the board will appear as a new port (often `/dev/ttyACM1`). Rerun `arduino-cli board list` to confirm, then pass the new port to the upload command.

### Port permission denied

On Linux, add your user to the `dialout` group:

```bash
sudo usermod -aG dialout $USER
```

Log out and back in for the change to take effect.

### Secrets file missing

`secrets.h` is not versioned. It must exist at `libraries/Statox_Config/secrets.h`. Copy the sample and fill in the values:

```bash
cp libraries/Statox_Config/secrets.sample.h libraries/Statox_Config/secrets.h
```
