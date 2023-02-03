# PingStatus
This is a small IoT device that pings a set of IP addresses and lights up LEDs depending on their status.  
It can be used to check if a service or website is reachable, or if a device has entered or left the local network.

<br>

## Features:
- Observes any amount of clients by pinging them via ICMP (private / public IP) or an HTTP request (URL)
- Automatically dims LEDs using PWM based on the ambient light level for optimal brightness level
- Automatically shuts off LEDs for even less light pollution at night
  - Momentary button to temporarily disable auto-shutoff mode
- Internal clock is updated with NTP, so it is always consistant and relatively accurate
- Many configuration settings for setting it up to exactly suit your needs

<br>

---

<br>

## Table of Contents:

- [Features](#features)
- [Parts list](#parts-list)
- [Setup](#setup)
- [Build](#build)
    - [Build Guide](#build-guide)
    - [Circuit Schematic](#circuit-schematic)
    - [Enclosure 3D Model](#enclosure-3d-model)

<br>

---

<br>

## Parts list:
- ESP board (ESP-8266 for example)  
  - Note: it needs to have at least 1 analog pin and 1 digital pin per observed client, plus 1 for the optional button
- Light Dependent Resistor (LDR)  
  - Wavelength: optimally around 480-540 nm - Resistance: doesn't really matter as a multiplier can be configured
  - This part and the pull-down resistor can be skipped if you disable auto dimming in the config
- 10 kΩ resistor (pull-down for LDR)
- Momentary push button or limit switch (normally open)
    - This part can also be skipped if you don't want to be able to temporarily disable the auto-shutoff mode
- Pre-perforated circuit board and a few wires for bridging
- Micro USB cable and USB power supply

Per observed client:
- LED
- ~150 Ω resistor  
  - Actual value depends on the forward voltage of the LED but 150 Ω *should* fit most

<br>

## Setup:
1. Install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Add your ESP board's URL in the IDE preferences [(guide)](https://arduino-esp8266.readthedocs.io/en/latest/installing.html)
3. Install your ESP board's firmware in the board manager
4. Install the ESP8266Ping library by [downloading it here](https://github.com/dancol90/ESP8266Ping/archive/refs/heads/master.zip) and extracting it to `<Arduino folder>/libraries`
5. Download PingStatus' repository by [clicking here](https://github.com/Sv443/PingStatus/archive/refs/heads/master.zip) and extract it somewhere
6. Rename the file `config.h.template` to `config.h`
7. Edit `config.h` to provide your WiFi settings and configure everything else to your needs
8. Open the .ino file with the Arduino IDE
9. Connect your ESP board to your computer via USB and wait for the drivers to be installed and ready
10. Match up the board settings under `Tools` with your ESP board and select the right COM or ttyUSB port
11. Hit the upload button
12. Open the serial monitor with <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>M</kbd> to verify if it works

<br>

## Build:
### Build Guide:
just connect the thingies to the thingies lol

<br>

### Circuit Schematic:
[Schematic coming soon]

<br>

### Enclosure 3D Model:
[Model coming soon]

<br>

<div align="center" style="text-align:center;">

Made with ❤️ by [Sv443](https://sv443.net/)  
If you like PingStatus, please consider [supporting the development](https://github.com/sponsors/Sv443)

</div>