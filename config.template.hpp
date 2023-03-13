#pragma once
#include "types.hpp"

//     ____             __ _
//    / ___|___  _ __  / _(_) __ _ _ 
//   | |   / _ \| '_ \| |_| |/ _` (_)
//   | |__| (_) | | | |  _| | (_| |_ 
//    \____\___/|_| |_|_| |_|\__, (_)
//                           |___/
//
// This file contains your WiFi password!
// Make sure to treat it accordingly!


/*************************************/
/*               Pins                */
/*************************************/

// GPIO pin of the manual refresh button (-1 to disable)
//   Can be any digital pin
#define PIN_BUTTON -1

// GPIO pin of the light dependent resistor (LDR)
//   This has to be an analog pin!
#define PIN_LDR -1


/*************************************/
/*               WiFi                */
/*************************************/

// WiFi access point SSID (name)
#define WIFI_SSID ""

// WiFi access point password
#define WIFI_PASSWORD ""


/*************************************/
/*               Time                */
/*************************************/

// Your time zone - possible values: https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
//#define TIME_ZONE TZ_Etc_UTC        // UTC
#define TIME_ZONE TZ_Europe_Berlin    // Europe, Berlin
//#define TIME_ZONE TZ_Etc_GMTp5      // GMT+5
//#define TIME_ZONE TZ_Etc_GMTm3      // GMT-3

// URL or IP to an NTP (time) server
//#define NTP_SERVER "pool.ntp.org"           // Default (uses the closest NTP server)
#define NTP_SERVER "192.168.178.1"            // Use a specific IP (like your router) as the NTP server
//#define NTP_SERVER "europe.pool.ntp.org"    // Closest NTP server in Europe
//#define NTP_SERVER "us.pool.ntp.org"        // Closest NTP server in the US


/*************************************/
/*              Clients              */
/*************************************/

// Timeout in milliseconds between refreshing the status of every client (default = 1 minute)
#define REFRESH_TIMEOUT 1000 * 60

// Internal buffer size of the clients string below (in bytes)
//   If you have lots of clients, you need to adjust this value so that there's enough room in memory to decode the clients string
//   To find out the optimal value, go to this site: https://arduinojson.org/v6/assistant
//   Select your board, choose "Deserialize" as the mode and "char*" as input type, then in the next step paste the object from below
//   Take the "Total (recommended)" value and round it up if you like to leave an extra buffer for future modifications
#define JSON_BUFFER_SIZE 512

// A JSON array of the clients you want to ping, which LED pins to light up and other configuration
//   The following table explains the JSON structure of a single client object
//   You may add as many client objects as you have GPIO pins with LEDs
//   - Note: You must adjust the JSON_BUFFER_SIZE above if you have lots of clients
//   - If you don't know JSON, check out this guide: https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/JSON
//   - The example value below has a size of 192 bytes TODO: ensure this is correct
//
//   | property      | type   |required?| default | description
//   |---------------|--------|---------|---------|-------------------------------------------------------
//   | name          | String | yes     |         | Name of the client (only used in the serial monitor)
//   | ip OR domain  | String | yes     |         | IP address or fully qualified domain name (e.g. "192.168.1.1" or "www.example.org")
//   | pin           | int    | yes     |         | Number of the GPIO pin to which an LED is connected
//   | activeLow     | bool   | no      | false   | Whether the LED is active low
//   | ldrMultiplier | float  | no      | 1.0     | Can be used to fine tune the brightness of the LED (2.0 is double, 0.5 is half)
//
// String clients = R"([
//   {
//     "name": "my cool phone",
//     "ip": "192.168.420.69",
//     "pin": 5,
//     "ldrMultiplier": 1.0,
//     "activeLow": false,
//   },
//   {
//     "name": "my cool website",
//     "domain": "www.sv443.net",
//     "pin": 14,
//     "ldrMultiplier": 0.5,
//     "activeLow": false,
//   }
// ])";


/*************************************/
/*          Serial Monitor           */
/*************************************/

// Whether the default USB serial monitor should be enabled
#define SERIAL_ENABLED true

// BAUD rate of the serial monitor
#define SERIAL_BAUD 115200

// This defines the amount of log messages you'll receive in the serial monitor
//   Possible values:
//   0 - Prints pretty much everything
//   1 - Prints only the most important info (default option)
//   2 - Only prints errors
#define SERIAL_LOG_LEVEL 1


/*************************************/
/*            Night Mode             */
/*************************************/

// If this is enabled, the LEDs will be turned off at night according to the settings below
#define NIGHT_MODE_ENABLED true

// Define the lower and upper boundary of the LDR (aka what values are considered the darkest and lightest)
//   The value has to be between 0 and 1023
//   If your SERIAL_LOG_LEVEL is set to 0 or 1, the serial monitor will print out the LDR's current value
#define LDR_MIN_VAL 0
#define LDR_MAX_VAL 500

// When to turn the LEDs off (24 hour format, local time)
#define NM_OFF_HOUR 23
#define NM_OFF_MIN  0

// When to turn the LEDs back on again (24 hour format, local time)
#define NM_ON_HOUR 6
#define NM_ON_MIN  0


/*************************************/
/*            Status LED             */
/*************************************/

// Whether the status LED (WiFi connection & activity indicator) should be enabled
#define STATUS_LED_ENABLED true

// Whether the status LED is active low (true on ESP builtin, false on Arduino builtin)
#define STATUS_LED_ACTIVE_LOW true

// Replace with a GPIO pin if you want an external status LED
#define STATUS_LED_PIN BUILTIN_LED
