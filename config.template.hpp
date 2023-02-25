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
#define PIN_BUTTON -1

// GPIO pin of the light dependent resistor (LDR)
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

// The clients to ping
//   TODO: explain JSON structure
String clients = R"([
  {
    "name": "my cool phone",
    "ip": "192.168.420.69",
    "pin": 5,
    "ldrMultiplier": 1.0,
    "activeLow": false,
  },
  {
    "name": "my cool website",
    "domain": "www.sv443.net",
    "pin": 14,
    "ldrMultiplier": 0.5,
    "activeLow": false,
  }
])";


/*************************************/
/*          Serial Monitor           */
/*************************************/

// Whether the default USB serial monitor should be enabled
#define SERIAL_ENABLED true

// BAUD rate of the serial monitor
#define SERIAL_BAUD 115200

// This defines the amount of log messages you'll receive in the serial monitor
//   Possible values:
//   LogLevel.Debug   - Prints pretty much everything
//   LogLevel.Info    - Prints only the most important info (default option)
//   LogLevel.Warning - Only prints warnings and errors
#define SERIAL_LOG_LEVEL LogLevel.Debug


/*************************************/
/*            Night Mode             */
/*************************************/

// If this is enabled, the LEDs will be turned off at night according to the settings below
//   The time is in the time zone you defined with TIME_ZONE
#define NIGHT_MODE_ENABLED true

// Define the lower and upper boundary of the LDR (aka what values are considered the darkest and lightest)
//   The value has to be between 0 and 1023
//   If your SERIAL_LOG_LEVEL is set to LogLevel.Debug the serial monitor will print out the LDR's current value
#define LDR_MIN_VAL 0
#define LDR_MAX_VAL 500

// When to turn the LEDs on (24 hour format)
#define NM_ON_HOUR 6
#define NM_ON_MIN  0

// When to turn the LEDs off (24 hour format)
#define NM_OFF_HOUR 23
#define NM_OFF_MIN  0


/*************************************/
/*            Status LED             */
/*************************************/

// Whether the status LED (WiFi connection & activity indicator) should be enabled
#define STATUS_LED_ENABLED true

// Whether the status LED is active low (true on ESP builtin, false on Arduino builtin)
#define STATUS_LED_ACTIVE_LOW true

// Replace with a GPIO pin if you want an external status LED
#define STATUS_LED_PIN BUILTIN_LED
