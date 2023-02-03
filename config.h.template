#pragma once
#include "types.h"

//     ____             __ _
//    / ___|___  _ __  / _(_) __ _ _ 
//   | |   / _ \| '_ \| |_| |/ _` (_)
//   | |__| (_) | | | |  _| | (_| |_ 
//    \____\___/|_| |_|_| |_|\__, (_)
//                           |___/
//
// This file contains your WiFi password!
// Make sure to treat it accordingly!


/*****************************/
/*           Time            */
/*****************************/

// Your time zone - possible values: https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
#define TIME_ZONE TZ_Etc_UTC          // UTC
//#define TIME_ZONE TZ_Europe_Berlin  // Europe, Berlin
//#define TIME_ZONE TZ_Etc_GMTp1      // GMT+1
//#define TIME_ZONE TZ_Etc_GMTm3      // GMT-3


/*****************************/
/*           WiFi            */
/*****************************/

// WiFi access point SSID (name)
#define WIFI_SSID ""

// WiFi access point password
#define WIFI_PASSWORD ""


/*****************************/
/*          Clients          */
/*****************************/

// Amount of clients that are being observed
#define CLIENTS_AMOUNT 2

// Enter all client IP addresses you'd like to observe and the GPIO pin of their LED
//   Note: The GPIO and digital pinouts are different! Check your board's pinout diagram to see which is which
//   If you want to make use of the auto-dimming, make sure the pins support PWM (squiggly line on your board's diagram)
//   If some of the pins don't support PWM, make sure to set AUTO_DIMMING_ENABLED to false
//   After changing this, please adjust CLIENTS_AMOUNT above
//
// Format:
//   ClientType  type               // Can be ClientType.IP or ClientType.URL
//   String      ipOrUrl            // IP address or URL
//   int         pin                // GPIO pin of the LED
//   int         ldrValueBounds[2]  // Lower and upper bounds of the LDR's value (can be between 0 and 1023) (only used if AUTO_DIMMING_ENABLED is true)
//   bool        activeLow          // If your LEDs are active low, set this to true, else false
//
PingClient clients[CLIENTS_AMOUNT] = {
  {
    ClientType.IP,
    "192.168.1.1",
    5,
    {0, 500},
    false,
  },
};

// Interval in milliseconds between sending pings (default = 10s/client)
//   Note: Anything under (10 seconds * amount of clients) might cause erratic or delayed behavior if the network and processing latency is too high
#define PING_INTERVAL 10000 * CLIENTS_AMOUNT


/*****************************/
/*       Auto-Dimming        */
/*****************************/

// Whether auto-dimming should be enabled
//   Requires all LEDs to be hooked up to PWM pins (squiggly line on your board's diagram)
#define AUTO_DIMMING_ENABLED true

// The maximum possible brightness of the LEDs as a value between 0.0 and 1.0
#define LED_MAX_VALUE 1.0
// The lowest possible brightness of the LEDs as a value between 0.0 and 1.0
#define LED_MIN_VALUE 0.025


// If this is enabled, the LEDs will be turned off according to the settings below
#define LED_OFF_ENABLED true

// When to turn the LEDs on (24 hours)
#define LED_ON_HOUR 6
#define LED_ON_MIN  0

// When to turn the LEDs off (24 hours)
#define LED_OFF_HOUR 24
#define LED_OFF_MIN  0


// NTP server pool URL
#define NTP_SERVER "de.europe.pool.ntp.org"
//#define NTP_SERVER "pool.ntp.org"           // Default (uses the closest NTP server)
//#define NTP_SERVER "europe.pool.ntp.org"    // European NTP server pool
//#define NTP_SERVER "us.pool.ntp.org"        // US NTP server pool


/*****************************/
/*           Other           */
/*****************************/

// Whether the status LED (WiFi connection & activity indicator) should be enabled
#define STATUS_LED_ENABLED true

// Whether the status LED is active low (true on ESP, false on Arduino)
#define STATUS_LED_ACTIVE_LOW true

// Set to a GPIO pin if you want an external status LED
#define STATUS_LED_PIN BUILTIN_LED

// Whether the serial monitor should be enabled
#define SERIAL_ENABLED true

// BAUD rate of the serial monitor
#define SERIAL_BAUD 115200

// Enable to get more debug output in the serial monitor
#define SERIAL_DEBUG true
