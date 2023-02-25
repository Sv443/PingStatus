#pragma once

#ifndef String
  #include <Arduino.h>
#endif

#include <ESP8266WiFi.h>
#include <time.h>
#include <TZ.h>

// https://github.com/dancol90/ESP8266Ping
#include <ESP8266Ping.h>
// https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

enum LogLevel {
  Debug = 0,
  Info,
  Error
};

enum ClientType {
  IP = 0,
  URL
};

struct PingClient {
  ClientType type;
  String ipOrUrl;
  int pin;
  float brightnessMultiplier;
  int ledValueBounds[2];
  bool activeLow;
};
