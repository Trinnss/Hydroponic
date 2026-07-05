# Hydroponic Monitor

ESP32-C3 + PlatformIO firmware for a hydroponic monitoring display. The current build reads an air sensor, a water temperature probe, and a water level value, then cycles an SH1106 OLED through multiple dashboard pages with a push button.

## Features

- 128x64 SH1106 OLED dashboard driven by U8g2
- Page cycling with a debounced button
- Air temperature and humidity from a DHT22
- Water temperature from a DS18B20 one-wire probe
- Water level status page and combined dashboard page
- Simple sensor error screens when a sensor is missing

## Hardware

Target board:

- ESP32-C3 DevKitM-1

Display:

- SH1106 128x64 OLED over I2C

Sensors and input:

- DHT22 on GPIO 1
- DS18B20 on GPIO 2
- Button on GPIO 3 with internal pull-up
- I2C SDA on GPIO 8
- I2C SCL on GPIO 9

## Pages

The display currently cycles through four pages:

1. Air temperature
2. Water temperature
3. Water level
4. Dashboard summary

If a sensor is not detected, the matching page shows an error message instead of values.

## Build And Upload

This project uses PlatformIO.

```powershell
pio run
pio run -t upload
pio device monitor
```

## Project Layout

- `src/main.cpp` initializes I2C, the display, the button, and the sensors
- `src/display.cpp` handles page selection and rendering
- `src/pages.cpp` contains the OLED drawing routines
- `src/sensors.cpp` reads the DHT22 and DS18B20
- `src/button.cpp` debounces the page button
- `platformio.ini` defines the ESP32-C3 build configuration and library dependencies

## Notes

- Serial logging is currently disabled in `main.cpp`
- Water level is still a placeholder value in `sensors.cpp`
- The project already includes `.gitignore` entries for PlatformIO build output

## Dependencies

Managed through `platformio.ini`:

- U8g2
- OneWire
- DallasTemperature
- Adafruit DHT sensor library