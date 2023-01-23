## PingStatus
This is a small IoT device that pings a set of IP addresses and lights up LEDs depending on their status.  
It can be used to check if a service or website is reachable, or if a device has entered or left the local network.

<br>

- [Parts list](#parts-list)
- [Setup](#setup)
- [Build](#build)

<br>

## Parts list:
- ESP board (ESP-8266 for example)

Per observed client:
- LED
- 100 Ω - 10 kΩ resistor (depends on how big the forward voltage of your LED is and how bright you want it; more resistance = dimmer)

<br>

## Setup:
1. Install the Arduino IDE
2. Add your ESP's board URL in the IDE preferences
3. Install your ESP board in the board manager
4. Install this library by downloading it and extracting it to `Arduino/libraries`  
    https://github.com/dancol90/ESP8266Ping
5. Download this repository and extract it
6. Rename the file `config.h.template` to `config.h`
7. Open the .ino file with the Arduino IDE
8. Provide your WiFi settings in `config.h` and configure everything else to your needs
9. Match up the board settings under `Tools` with your ESP board
10. Hit the upload button

<br>

## Build:
just connect the thingies to the thingies lol  
[Schematic coming soon]

<br>

<div align="center" style="text-align:center;">

Made with ❤️ by [Sv443](https://sv443.net/)  
If you like PingStatus, please consider [supporting the development](https://github.com/sponsors/Sv443)

</div>