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

- `PUT /api/network`: Set network configuration. Supports form parameters
                      `ssid` and `pass`
- `PUT /api/state`: Set desired program, color and effect. Currently
                    supports form parameters `program` (int) and
                    `brightness` (float).
- `PUT /api/ota`: Start or stop OTA support. Supports form parameter
                  `command` (str). Supported commands are `start` and
                  `stop`.
- `POST /api/restart`: Reboot device

# TODO

## System
- Create and add HTML pages:
  - home (program, color, effect selection)
- Create and add API functionality:
  - Get available programs, colors, effects
  - Set colors, effects
- Add captive portal in WiFi mode:
    - https://github.com/tzapu/WiFiManager/blob/master/WiFiManager.cpp
    - https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/CaptivePortalAdvanced.ino
    NOTE: Currently build but sadly it's crashing the ESP, watchdog is triggered.

## Programs and functionality

- Create support for following functions
    - Colorless programs (all LEDs on, certain LEDs on)
    - Static color programs (green/white idea)
    - Dynamic color programs (moving rainbow concepts)
    - Color effects: Apply color to colorless programs: static color, slowly changing color, etc
    - Brightness effects: Apply dynamice brightness effects to colorless & static color programs: pulse, slow left-right etc.
- Create custom programs through web interface
