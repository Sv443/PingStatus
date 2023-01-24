#ifndef String
  #include "Arduino.h"
#endif

#include "config.h"
#include "types.h"

// https://github.com/dancol90/ESP8266Ping
#include <ESP8266Ping.h>

#include <time.h>
#include <TZ.h>


/** Raw time object */
time_t now;
/** More convenient time wrapper */
tm tm;

void setup() {
  #if SERIAL_ENABLED
    Serial.begin(SERIAL_BAUD);

    Serial.println();
    Serial.println("PingStatus by Sv443 (https://github.com/Sv443)");
    Serial.println();

    #if PING_INTERVAL < 30000
      Serial.println("!!");
      Serial.println("!! Warning: Setting PING_INTERVAL below ~30s might cause erratic or delayed behavior if the network and processing latency is too high");
      Serial.println("!!");
    #endif
  #endif

  #if AUTO_DIMMING_ENABLED
    configTime(TIME_ZONE, NTP_SERVER);
  #endif

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  #if SERIAL_ENABLED
    Serial.print("WiFi connecting");
  #endif

  #if STATUS_LED_ENABLED
    pinMode(STATUS_LED_PIN, OUTPUT);
  #endif
  int ledState = ACTIVE_LOW ? HIGH : LOW;

  while(WiFi.status() != WL_CONNECTED) {
    #if SERIAL_ENABLED
      Serial.print(".");
    #endif

    #if STATUS_LED_ENABLED
      digitalWrite(STATUS_LED_PIN, ledState);
      ledState = ledState == HIGH ? LOW : HIGH;
    #endif

    delay(500);
  }

  digitalWrite(STATUS_LED_PIN, ACTIVE_LOW ? LOW : HIGH);

  #if SERIAL_ENABLED
    Serial.println();
  #endif

  for (int i = 0; i < CLIENTS_AMOUNT; i++)
    pinMode(clients[i].pin, OUTPUT);
}

/** Updates the globals `now` and `tm` with the current time */
void updateTime() {
  time(&now);
  localtime_r(&now, &tm);
}

void loop() {
  for(int i = 0; i < CLIENTS_AMOUNT; i++) {
    IPAddress ip = clients[i].ip;
    int pin = clients[i].pin;

  #if SERIAL_ENABLED
    Serial.print("Pinging client #");
    Serial.print(i + 1);
    Serial.print(" (IP: ");
    Serial.print(ip);
    Serial.print(" - Pin: ");
    Serial.print(pin);
    Serial.println(")");
  #endif

    bool pingRes = Ping.ping(ip);

    if(pingRes) {
      #if SERIAL_ENABLED
        Serial.print("  > Client #");
        Serial.print(i + 1);
        Serial.println(" is available");
      #endif
    }
    else {
      #if SERIAL_ENABLED
        Serial.print("  > Client #");
        Serial.print(i + 1);
        Serial.println(" is not available");
      #endif
    }

    updateLedState(pin, pingRes);
  }

  delay(PING_INTERVAL);
}

/** Updates the LED at `pin` to be `enabled` or not, using the optional brightness and dim values set in config.h */
void updateLedState(int pin, bool enabled) {
  #if AUTO_DIMMING_ENABLED
    updateTime();

    #if SERIAL_ENABLED
      Serial.print("Current time: ");
      Serial.print(tm.tm_hour);
      Serial.print(":");
      Serial.print(tm.tm_min);
      Serial.print(":");
      Serial.println(tm.tm_sec);
    #endif

    uint16 brightThresholdMins = LED_BRIGHT_HOUR * 60 + LED_BRIGHT_MIN;
    uint16 dimThresholdMins = LED_DIM_HOUR * 60 + LED_DIM_MIN;

    bool bright = tm.tm_hour * 60 + tm.tm_min >= brightThresholdMins
      && tm.tm_hour * 60 + tm.tm_min < dimThresholdMins;

    #if SERIAL_ENABLED
      Serial.print("Setting LED at pin ");
      Serial.print(pin);
      Serial.print(" to enabled ");
      Serial.println(bright ? "(bright)" : "(dim)");
    #endif
    if(bright) {
      int val = enabled ? floor(LED_BRIGHT_VALUE * 1024) : 0;
      analogWrite(pin, val);
    }
    else {
      int val = enabled ? floor(LED_DIM_VALUE * 1024) : 0;
      Serial.println(val);
      analogWrite(pin, val);
    }
  #else
    digitalWrite(pin, enabled);
    #if SERIAL_ENABLED
      Serial.print("Setting LED at pin ");
      Serial.print(pin);
      Serial.print(" to ");
      Serial.println(enabled ? "enabled" : "disabled");
    #endif
  #endif
}
