#ifndef String
  #include "Arduino.h"
#endif

#include "config.hpp"
#include "utils.hpp"
#include "types.hpp"


/** Raw time object */
time_t now;
/** More convenient time wrapper */
tm tm;

void setup() {
  #if SERIAL_ENABLED
    Serial.begin(SERIAL_BAUD);
    Serial.println("\n>> PingStatus by Sv443: https://github.com/Sv443/PingStatus\n");
  #endif

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  debug("WiFi connecting");

  #if STATUS_LED_ENABLED
    pinMode(STATUS_LED_PIN, OUTPUT);
  #endif
  uint8_t statusLedState = STATUS_LED_ACTIVE_LOW ? HIGH : LOW;

  while(WiFi.status() != WL_CONNECTED) {
    #if SERIAL_ENABLED && SERIAL_LOG_LEVEL <= LogLevel.Info
      Serial.print(".");
    #endif

    #if STATUS_LED_ENABLED
      digitalWrite(STATUS_LED_PIN, statusLedState);
      statusLedState ^= statusLedState;
    #endif

    delay(500);
  }

  digitalWrite(STATUS_LED_PIN, ACTIVE_LOW ? LOW : HIGH);

  #if SERIAL_ENABLED && SERIAL_LOG_LEVEL <= LogLevel.Info
    Serial.println();
  #endif

  // TODO: read JSON client config

  // TODO: resolve domains

  // TODO: set pin modes
  // for (int i = 0; i < CLIENTS_AMOUNT; i++)
  //   pinMode(clients[i].pin, OUTPUT);
}

// internal timer increments per second
#define INT_TIMER_RES 10
uint32_t intTimer = 0;

void loop() {
  // update time globals
  time(&now);
  localtime_r(&now, &tm);

  // read & remap LDR val
  float ldrVal = map(max(LDR_MIN_VAL, min(analogRead(PIN_LDR), LDR_MAX_VAL)), LDR_MIN_VAL, LDR_MAX_VAL, 0.0, 1.0);

  if(intTimer % INT_TIMER_RES === 0)
    debug("Time: " + tm.tm_hour + ":" + tm.tm_min + ":" + tm.tm_sec + " - LDR value: " + analogRead(PIN_LDR), LogLevel.Debug)

  // TODO: ping clients

  // TODO: update led states

  delay(1000 / INT_TIMER_RES);
  intTimer++;
}

/** Checks if the global `tm` is between the `min` and `max` timestamps in minutes */
bool timeBetweenTimestamps(uint16 min, uint16 max) {
  return tm.tm_hour * 60 + tm.tm_min >= min
    && tm.tm_hour * 60 + tm.tm_min < max;
}
