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

<br><br>

## Parts list:
### Required parts:
> - ESP board (ESP-8266 for example)
>     - Note: it needs to have at least 1 analog pin and 1 digital pin per observed client, plus 1 for the optional push button
> - Pre-perforated circuit board and a few wires for bridging
> - Micro USB cable and USB power supply

<br>

### Parts needed per observed client:
> - LED of any color
> - ~150 Ω resistor
>     - Value depends on the forward voltage of the LED but 150 Ω *should* fit most

<br>

### Optional parts:
> - Light Dependent Resistor / Photoresistor (LDR)
>     - Wavelength: optimally around 480-540 nm - Resistance: doesn't really matter as a multiplier can be configured
> - 10 kΩ pull-down resistor for LDR  
>   
> These parts can be skipped if you disable auto dimming in the config  

<br>

> - Momentary push button or limit switch (normally open)
> - 10 kΩ pull-down resistor for push button  
>   
> These parts can also be skipped if you don't want to be able to temporarily disable the auto-shutoff mode

<br><br>

## Setup:
1. Install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Add your ESP board's URL in the IDE preferences by following [this guide](https://arduino-esp8266.readthedocs.io/en/latest/installing.html)
3. Install your ESP board's firmware in the board manager
4. Install the following libraries by downloading them and extracting them to `<Arduino folder>/libraries` (usually under "Documents"):
    - [ESP8266Ping](https://github.com/dancol90/ESP8266Ping/archive/refs/heads/master.zip)
    - [ArduinoJson](https://github.com/bblanchon/ArduinoJson/archive/refs/heads/master.zip)
5. [Download the PingStatus repository](https://github.com/Sv443/PingStatus/archive/refs/heads/master.zip) and extract it somewhere
6. Rename the file `config.h.template` to `config.h`
7. Edit `config.h` to provide your WiFi settings and configure everything else to your needs
8. Open the .ino file with the Arduino IDE
9. Connect your ESP board to your computer via USB and wait for the drivers to be installed and ready
10. Match up the board settings under `Tools` with your ESP board and select the right COM or ttyUSB port
11. Hit the upload button
12. Open the serial monitor with <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>M</kbd> to verify that it works
    - If the output is garbled, reset the board. If it is still unreadable, make sure the BAUD rate is set to 115200.

<br><br>

## Build:
### Build Guide:
just connect the thingies to the thingies lol

<br>

### Circuit Schematic:
[Schematic coming soon]

<br>

### Enclosure 3D Model:
[Model coming soon]

<br><br><br>

<div align="center" style="text-align:center;">

Made with ❤️ by [Sv443](https://sv443.net/)  
If you like PingStatus, please consider [supporting the development](https://github.com/sponsors/Sv443)

</div>