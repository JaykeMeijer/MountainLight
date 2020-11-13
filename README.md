# MountainLight

ESP32 code for a WiFi enabled wall mounted light consisting of WS2812b LEDs.

The ESP will boot when powered on. It will run an init sequence on the light
while in the background setting up: Read previous state, connect to WiFi.

All 'management' functionality (API, system init) is run on Core 0, as xTask.
LED control remains on core 1. A shared state is used to change the functioning
of the LED control.

If no wifi params are stored, the stored params are incorrect or the network is
not available, an access point is created so these can be configured.

System config is stored on EEPROM. Max stored SSID size is 32 chars, same for
password.

# Networking

mDNS is on, the device is known as `mountainlight.local`. 

# HTML Endpoints

- `/`: Home
- `/config`: Connectivity config page

# API

The following API calls are currently supported:

- `GET /api/network`: Get current network configuration as well as
                      available networks.
- `PUT /api/network`: Set network configuration. Supports form parameters
                      `ssid` and `pass`
- `GET /api/options`: Get the available programs, colors and effects
- `GET /api/state`: Get the current state: active programs etc.
- `PUT /api/state`: Set desired program, color and effect. Currently
                    supports form parameters `program` (int), `effect`
                    (int), `brightness` (float), `effect_speed` (int),
                    `color_mode` (int), `color_speed` (int) and `color_<r/g/b>`
                    (int). Note that for a new color to be set, all three
                    components need to be provided.
- `PUT /api/ota`: Start or stop OTA support. Supports form parameter
                  `command` (str). Supported commands are `start` and
                  `stop`.
- `POST /api/restart`: Reboot device
- `GET /api/debug`: Get debug information. Currently only returns
                    number of 'missed' frames, the frames that could not
                    be processed in time.

# TODO

## System

- Homepage: Indicate active program, effect.
- Create and add API functionality:
  - Get available programs (hardcoded - frame based programs?)
- Add captive portal in WiFi mode:
    - https://github.com/tzapu/WiFiManager/blob/master/WiFiManager.cpp
    - https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/CaptivePortalAdvanced.ino
    NOTE: Currently build but sadly it's crashing the ESP, watchdog is triggered.
- Performance enhancements - currently missing quite some frames

## Programs and functionality

- Create support for following functions
    - Custom Programs
- Create custom programs through web interface

## Specific programs to add

- Color:
  - Primary color loop
  - Secondary color loop
  - ?
- Brightness Effects:
  - ?
