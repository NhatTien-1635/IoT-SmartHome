# IoT Climate Control with TinyML

This project is an ESP32-based IoT climate controller that reads temperature and humidity, runs TinyML inference on-device, and controls a fan through a web dashboard. It is built with PlatformIO and uses FreeRTOS tasks to keep sensing, control, Wi-Fi, and AI inference running in parallel.

## Overview

The firmware turns the ESP32 into a small smart climate node that can:

- Measure temperature and humidity with a DHT22 sensor
- Run a TensorFlow Lite Micro model for inference
- Switch fan operation between OFF, ON, and AUTO modes
- Host a local web interface for monitoring and control
- Configure Wi-Fi via a captive portal when no credentials are saved

## Features

- Real-time sensor monitoring with a DHT22 sensor
- FreeRTOS-based multitasking architecture
- TinyML inference running on the ESP32
- Fan control with manual and automatic modes
- Web dashboard served from LittleFS
- Wi-Fi configuration through a built-in access point
- JSON API for sensor values

## Hardware Requirements

- ESP32 DevKit (tested with ESP32 DevKit v1)
- DHT22 temperature and humidity sensor
- Fan module or relay-compatible actuator
- USB cable for programming and serial monitoring

## Project Structure

```text
├── data/
│   ├── dashboard.html          # Web dashboard served over HTTP
│   └── wifi_config.html        # Wi-Fi setup page
├── include/
│   ├── Global.h                # Shared definitions and globals
│   ├── Task_BlinkingLED.h
│   ├── Task_FanControl.h
│   ├── Task_TempHumidMonitor.h
│   ├── Task_TinyML.h
│   └── Task_WebServer.h
├── src/
│   ├── main.cpp                # Entry point and task creation
│   ├── Task_BlinkingLED.cpp    # LED heartbeat task
│   ├── Task_FanControl.cpp     # Fan control logic
│   ├── Task_TempHumidMonitor.cpp
│   ├── Task_WebServer.cpp      # Wi-Fi + web server logic
│   ├── TinyML.cpp              # TensorFlow Lite Micro inference task
│   └── ...
├── TiniML/
│   └── tinyml.py               # TinyML-related helper script
├── platformio.ini              # PlatformIO configuration
└── README.md
```

## How It Works

The firmware creates several concurrent tasks:

1. Blink task
   - Toggles the onboard LED every second as a heartbeat.

2. Temperature and humidity task
   - Reads the DHT22 sensor and stores recent values in shared buffers.

3. Fan control task
   - Reads the current fan mode and either turns the fan on, off, or uses the inference result in AUTO mode.

4. Web server task
   - Starts Wi-Fi in either station or access-point mode
   - Serves the dashboard and handles configuration requests
   - Exposes endpoints for sensor data and fan toggling

5. TinyML task
   - Loads the compiled TensorFlow Lite model
   - Feeds sensor values into the model
   - Uses the inference output to decide fan behavior

## Wi-Fi and Web Interface

On first boot, the ESP32 starts an access point named:

- SSID: ESP32-AccessPoint
- Password: 12345678

You can connect to that network and open the configuration page to enter your home Wi-Fi credentials. After a successful connection, the device serves the dashboard from the built-in web server.

### Available endpoints

- / - Dashboard or configuration page
- /wifi - Wi-Fi configuration page
- /save - Saves Wi-Fi credentials
- /toggleFan - Toggles the fan mode
- /api/sensors - Returns JSON sensor values

## Build and Upload

### Prerequisites

- VS Code
- PlatformIO extension
- ESP32 board support installed in PlatformIO

### Steps

1. Open the project folder in VS Code.
2. Ensure the PlatformIO extension is installed and the environment is detected.
3. Connect the ESP32 via USB.
4. Build the project using the PlatformIO build command.
5. Upload the firmware to the board.
6. Open the serial monitor at 115200 baud to view logs.

## Configuration Notes

- Default Wi-Fi access point credentials are defined in the firmware.
- The DHT pin and type are configured in the shared header.
- The fan control pins are currently set to GPIO 25 and GPIO 26.

## Example Serial Output

```text
[Time: 0] MANUAL -> FAN OFF
[Time: 1] MANUAL -> FAN ON
[Time: 2] AUTO Temerature: 28.500000, Humidity: 65.000000 -> FAN ON
Inference: 0.812500
```

## Notes

- The project uses LittleFS to serve HTML files from the data folder.
- The current implementation uses the ESP32’s PWM output for fan control and can be expanded with a real motor driver or relay board.
- The TinyML model and inference logic are wired into the firmware and can be replaced or retrained as needed.
- The physical fan in this setup is currently not available for testing because it is broken, so the firmware logs fan state through the serial monitor instead of driving a real fan during validation.

## License

This project is intended for educational and prototyping use.
