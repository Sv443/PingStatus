#ifndef _TYPES_HPP
#define _TYPES_HPP

#ifndef String
  #include <Arduino.h>
#endif
#include <vector>

#include <ESP8266WiFi.h>
#include <time.h>
#include <TZ.h>

// https://github.com/dancol90/ESP8266Ping
#include <ESP8266Ping.h>
// https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

struct PingClient {
  String name;
  IPAddress ip;
  int pin;
  bool activeLow;
  float ldrMultiplier;
};


#endif
