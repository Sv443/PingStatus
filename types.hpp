#pragma once

#include <ESP8266WiFi.h>
#include <time.h>
#include <TZ.h>

// https://github.com/dancol90/ESP8266Ping
#include <ESP8266Ping.h>
// https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

enum ClientType {
  IP,
  URL
};

typedef struct {
  ClientType type;
  String ipOrUrl;
  int pin;
  float brightnessMultiplier;
  int ledValueBounds[2];
  bool activeLow;
} PingClient;
