# Hydroponic Monitor

Hydroponic Monitor is an ESP32-C3 firmware project built with PlatformIO. It drives a 128x64 SH1106 OLED and cycles through several sensor pages for a small hydroponic setup. The firmware currently reads air temperature and humidity from a DHT22, water temperature from a DS18B20, and a placeholder water level value that is ready to be replaced with a real analog or digital sensor input.

## Overview

The firmware boots the display, configures I2C, initializes the sensors, and then enters a simple loop:

1. Read the page button with debounce logic.
2. Sample the sensors once per second.
3. Render the active screen on the OLED.

The display uses U8g2 for all drawing, and the layout is split into separate page functions so each screen can evolve independently.

## Features

- 128x64 SH1106 OLED interface
- Four display pages with a button-controlled page index
- Debounced input on the page button
- DHT22 support for air temperature and humidity
- DS18B20 support for water temperature
- Combined dashboard page for a quick system overview
- Error screens when a sensor is missing or disconnected

## Hardware

Target board:

- ESP32-C3 DevKitM-1

Display:

- SH1106 128x64 OLED over I2C

Inputs and sensors:

- DHT22 on GPIO 1
- DS18B20 on GPIO 2
- Page button on GPIO 3 with internal pull-up
- I2C SDA on GPIO 8
- I2C SCL on GPIO 9

## Wiring Notes

- The button uses `INPUT_PULLUP`, so it should be wired to pull the pin low when pressed.
- The DHT22 and DS18B20 need proper pull-up resistors as required by their modules or breakout boards.
- The OLED uses the hardware I2C bus configured in `main.cpp`.

## Display Pages

The OLED cycles through four pages:

1. Air temperature page
2. Water temperature page
3. Water level page
4. Dashboard page

Each page uses a different visual layout, including large numeric readouts, bars, and simple status text. If the DHT22 or DS18B20 is not detected, the matching page shows a sensor error message instead of live data.

## Software Behavior

### Button Handling

`src/button.cpp` reads the button state with a 50 ms debounce window. Each press increments the page number and wraps back to page 1 after page 4.

### Sensor Reading

`src/sensors.cpp` reads the sensors once per second to avoid unnecessary polling. The DHT22 updates `airTemp` and `humidity`, while the DS18B20 updates `waterTemp`.

### Rendering

`src/display.cpp` decides which page to draw and calls the matching function from `src/pages.cpp`. It also draws the small page indicator dots at the bottom of the screen.

## Current Status

- Air temperature and humidity are read from the DHT22
- Water temperature is read from the DS18B20
- Water level is still a fixed placeholder value in `sensors.cpp`
- Serial logging is currently disabled in `main.cpp`

## Build And Upload

This project uses PlatformIO.

```powershell
pio run
pio run -t upload
pio device monitor
```

If you are using VS Code, you can also use the PlatformIO sidebar to build, upload, and open the serial monitor.

## Project Layout

- `src/main.cpp` initializes I2C, the display, the button, and the sensors
- `src/button.cpp` handles button debounce and page switching
- `src/display.cpp` selects the active page and draws the screen
- `src/pages.cpp` contains the OLED drawing routines for each page
- `src/sensors.cpp` reads the DHT22 and DS18B20 values
- `include/*.h` contains the shared interfaces used across the firmware
- `platformio.ini` defines the ESP32-C3 build configuration and libraries

## Dependencies

Managed through `platformio.ini`:

- U8g2
- OneWire
- DallasTemperature
- Adafruit DHT sensor library

## Extending The Project

Common next steps for this firmware are:

- Replace the placeholder water level value with a real sensor reading
- Add serial logging for debugging and calibration
- Tune the OLED layouts for different sensor ranges
- Add alarm thresholds for temperature or low water level
- Add a fifth page for pump, fan, or nutrient status

## Troubleshooting

- If the display stays blank, check the I2C wiring and confirm the OLED address and model.
- If the DHT22 page shows an error, verify the pin assignment, power, and pull-up requirements.
- If the DS18B20 reads as disconnected, check the one-wire data line and pull-up resistor.
- If the button skips pages, confirm the wiring to GPIO 3 and the debounce timing.

## Notes

- The project already includes `.gitignore` entries for PlatformIO build output.