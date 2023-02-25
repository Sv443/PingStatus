#include "config.hpp"
#include "types.hpp"


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
    Serial.print("\nPinging client #");
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
        Serial.println(" is available\n");
      #endif
    }
    else {
      #if SERIAL_ENABLED
        Serial.print("  > Client #");
        Serial.print(i + 1);
        Serial.println(" is not available\n");
      #endif
    }

    // TODO: collect LED states in a variable, then update at the end to update all at once
    updateLedState(pin, pingRes);
  }

  // TODO: change to like 100ms, then calculate amount of interval with PING_INTERVAL
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

    // TODO:
    // 1. read LDR analog value
    // 2. offset / multiply by value from config.h
    // 3. clamp between 0 and 10 to reduce resolution and "jitter"
    // 4. set LED brightness

    bool ledsOn = betweenThreshold(ledsOnThreshold, ledsOffThreshold);
    bool bright = true; // TODO

    if(!ledsOn) {
      analogWrite(pin, 0);

      // TODO: status led blink sequence to notify of the LEDs turning off
      // maybe the LEDs should blink too?
      #if SERIAL_ENABLED && SERIAL_DEBUG
        Serial.print("Setting LED at pin ");
        Serial.print(pin);
        Serial.println(" to disabled (off period)");
      #endif

      return;
    }

    #if SERIAL_ENABLED && SERIAL_DEBUG
      Serial.print("Setting LED at pin ");
      Serial.print(pin);
      Serial.print(" to enabled ");
      Serial.println(bright ? "(on & bright period)" : "(on & dim period)");
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
    Serial.print("Setting LED at pin ");
    Serial.print(pin);
    Serial.print(" to ");

    if(!ledsOn) {
      digitalWrite(pin, LOW);

      // TODO: status led blink sequence to notify of the LEDs turning off
      // maybe the LEDs should blink too?
      #if SERIAL_ENABLED && SERIAL_DEBUG
        Serial.println("disabled (off period)");
      #endif
    }
    else {
      digitalWrite(pin, enabled);

      #if SERIAL_ENABLED && SERIAL_DEBUG
        Serial.print(enabled ? "enabled" : "disabled");
        Serial.println(" (on period)");
      #endif
    }
  #endif
}

/** Checks if the global `tm` is between the `min` and `max` thresholds in minutes */
bool timeBetweenThreshold(uint16 min, uint16 max) {
  return tm.tm_hour * 60 + tm.tm_min >= min
    && tm.tm_hour * 60 + tm.tm_min < max;
}

/** Parses an IPv4 string to an IPAddress instance */
IPAddress parseIP(String ip) {
  // TODO: parse IP
  return IPAddress(1, 2, 3, 4);
}
