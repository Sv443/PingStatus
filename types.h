#pragma once

#include <ESP8266WiFi.h>
#include <time.h>
#include <TZ.h>

typedef struct {
  IPAddress ip;
  int pin;
} PingClient;
