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

# HTML Endpoints

- `/`: Home
- `/config`: Connectivity config page

# API

The following API calls are currently supported:

- `PUT /api/network`: Set network configuration. Supports form parameters
                      `ssid` and `pass`
- `PUT /api/state`: Set desired program, color and effect. Currently only
                    supports form parameter `program` (int).
- `POST /api/restart`: Reboot device

# TODO

## System
- Add SPIFFS & FileBrowser
- Create and add HTML pages:
  - home (program, color, effect selection)
  - config (WiFi settings)
- Create and add API functionality:
  - Get available network list
  - Get available programs, colors, effects
  - Set colors, effects
- Add OTA updates
- Add captive portal in WiFi mode:
    - https://github.com/tzapu/WiFiManager/blob/master/WiFiManager.cpp
    - https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/CaptivePortalAdvanced.ino
- Add mDNS name as mountainlight.local or whatever when on wifi

## Programs and functionality

- Create support for following functions
    - Colorless programs (all LEDs on, certain LEDs on)
    - Static color programs (green/white idea)
    - Dynamic color programs (moving rainbow concepts)
    - Color effects: Apply color to colorless programs: static color, slowly changing color, etc
    - Brightness effects: Apply dynamice brightness effects to colorless & static color programs: pulse, slow left-right etc.
    - Master Brightness
- Create custom programs through web interface
