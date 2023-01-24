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

    #if UPDATE_INTERVAL < 30000
      Serial.println("!!");
      Serial.println("!! Warning: Setting UPDATE_INTERVAL below ~30s might lead to erratic behavior");
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

  delay(UPDATE_INTERVAL);
}

/** Updates the LED at `pin` to be `enabled` or not, using the optional brightness and dim values set in config.h */
void updateLedState(int pin, bool enabled) {
  #if AUTO_DIMMING_ENABLED
    updateTime();

    bool bright = tm.tm_hour >= LED_BRIGHT_HOUR && tm.tm_min >= LED_BRIGHT_MIN
      && tm.tm_hour < LED_DIM_HOUR && tm.tm_min < LED_DIM_MIN;

    if(bright)
      analogWrite(pin, floor(LED_BRIGHT_VALUE * 1024));
    else
      analogWrite(pin, floor(LED_DIM_VALUE * 1024));
  #else
    digitalWrite(pin, enabled);
  #endif
}
