#ifndef String
  #include "Arduino.h"
#endif

#include "types.h"
#include "config.h"

// https://github.com/dancol90/ESP8266Ping
#include <ESP8266Ping.h>

void setup()
{
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

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  #if SERIAL_ENABLED
    Serial.print("Connecting to the WiFi AP");
  #endif

  #if STATUS_LED_ENABLED
    pinMode(STATUS_LED_PIN, OUTPUT);
  #endif
  int ledState = ACTIVE_LOW ? HIGH : LOW;

  while (WiFi.status() != WL_CONNECTED)
  {
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

void loop()
{
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

    if(Ping.ping(ip)) {
      #if SERIAL_ENABLED
        Serial.print("  > Client #");
        Serial.print(i + 1);
        Serial.println(" is available");
      #endif
      digitalWrite(pin, ACTIVE_LOW ? LOW : HIGH);
    }
    else {
      #if SERIAL_ENABLED
        Serial.print("  > Client #");
        Serial.print(i + 1);
        Serial.println(" is not available");
      #endif
      digitalWrite(pin, ACTIVE_LOW ? HIGH : LOW);
    }
  }

  delay(UPDATE_INTERVAL);
}
