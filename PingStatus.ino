#ifndef String
  #include "Arduino.h"
#endif

#include "types.hpp"
#include "config.hpp"
#include "utils.hpp"


// A JSON array of the clients you want to ping, which LED pins to light up and other configuration
//   The following table explains the JSON structure of a single client object
//   You may add as many client objects as you have GPIO pins with LEDs
//   - Note: You must adjust the JSON_BUFFER_SIZE above if you have lots of clients
//   - If you don't know JSON, check out this guide: https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/JSON
//   - The example value below has a size of 192 bytes TODO: ensure this is correct
//
//   | property      | type   |required?| default | description
//   |---------------|--------|---------|---------|-------------------------------------------------------
//   | name          | String | yes     |         | Name of the client (only used in the serial monitor)
//   | ip OR domain  | String | yes     |         | IP address or fully qualified domain name (e.g. "192.168.1.1" or "www.example.org")
//   | pin           | int    | yes     |         | Number of the GPIO pin to which an LED is connected
//   | activeLow     | bool   | no      | false   | Whether the LED is active low
//   | ldrMultiplier | float  | no      | 1.0     | Can be used to fine tune the brightness of the LED (2.0 is double, 0.5 is half)
//
char* clients = R"(
[
  {
    "name": "pc",
    "ip": "192.168.178.56",
    "pin": 5,
    "ldrMultiplier": 1.0,
    "activeLow": false,
  },
  {
    "name": "svn",
    "domain": "www.sv443.net",
    "pin": 14,
    "ldrMultiplier": 1.0,
    "activeLow": false,
  }
]
)";


/** Raw time object */
time_t now;
/** More convenient time wrapper */
tm tm;

uint8_t getClientsAmt(DynamicJsonDocument &doc, String requiredKey);
std::vector<PingClient> getClients(DynamicJsonDocument &doc, uint8_t clientsAmt);

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
    #if SERIAL_ENABLED && SERIAL_LOG_LEVEL <= 1
      Serial.print(".");
    #endif

    #if STATUS_LED_ENABLED
      digitalWrite(STATUS_LED_PIN, statusLedState);
      statusLedState ^= statusLedState;
    #endif

    delay(500);
  }

  digitalWrite(STATUS_LED_PIN, STATUS_LED_ACTIVE_LOW ? LOW : HIGH);

  #if SERIAL_ENABLED && SERIAL_LOG_LEVEL <= 1
    Serial.println();
  #endif

  DynamicJsonDocument doc(JSON_BUFFER_SIZE);
  deserializeJson(doc, clients);

  // read JSON client config
  uint8_t clientsAmt = getClientsAmt(doc, "pin");
  debug("Found " + String(clientsAmt) + " clients in the config", 0);

  std::vector<PingClient> pingClients = getClients(doc, clientsAmt);

  // #DEBUG
  Serial.println("Client " + pingClients[0].name + " @ " + pingClients[0].ip.toString());
  Serial.println("Client " + pingClients[1].name + " @ " + pingClients[1].ip.toString());

  // TODO: resolve domains

  // TODO: set pin modes
  // for (int i = 0; i < CLIENTS_AMOUNT; i++)
  //   pinMode(clients[i].pin, OUTPUT);

  // TODO: attach button interrupt
}

/** Returns the amount of client objects in the config */
uint8_t getClientsAmt(DynamicJsonDocument &doc, String requiredKey) {
  uint8_t i = 0;
  while(doc[i].containsKey(requiredKey))
    i++;
  return i;
}

std::vector<PingClient> getClients(DynamicJsonDocument &doc, uint8_t clientsAmt) {
  std::vector<PingClient> pingClients;

  for(uint8_t i = 0; i < clientsAmt; i++) {
    // required
    String name = doc[i]["name"].as<String>();
    int pin = doc[i]["name"].as<int>();

    // either ip or domain
    IPAddress clientIp;
    if(doc[i].containsKey("ip") && !clientIp.fromString(doc[i]["ip"].as<String>()))
      debug("Couldn't parse IP address of client '" + name + "'");
    IPAddress ip = doc[i].containsKey("ip") ? clientIp : resolveIp(doc[i]["domain"].as<String>());

    // optional with default
    bool activeLow = doc[i].containsKey("activeLow") ? doc[i]["activeLow"].as<bool>() : false;
    float ldrMultiplier = doc[i].containsKey("ldrMultiplier") ? doc[i]["ldrMultiplier"].as<float>() : 1.0f;

    pingClients.push_back({ name, ip, pin, activeLow, ldrMultiplier });
  }

  return pingClients;
}

/** Resolves a FQDN to an IP address at the local gateway */
IPAddress resolveIp(String fqdn) {
  IPAddress ip;
  if(!WiFi.hostByName(fqdn.c_str(), ip)) {
    debug("Couldn't resolve hostname '" + fqdn + "'", 2);
    Serial.println("\n\n>> Resetting ESP...\n\n");
    ESP.reset();
  }
  return ip;
}

// amount of internal timer increments per second
#define INT_TIMER_RES 10
uint32_t intTimer = 0;

void loop() {
  // update time globals
  time(&now);
  localtime_r(&now, &tm);

  // read & remap LDR val
  float ldrVal = map(max(LDR_MIN_VAL, min(analogRead(PIN_LDR), LDR_MAX_VAL)), LDR_MIN_VAL, LDR_MAX_VAL, 0.0, 1.0);

  if(intTimer % INT_TIMER_RES == 0)
    debug("Time: " + String(tm.tm_hour) + ":" + String(tm.tm_min) + ":" + String(tm.tm_sec) + " - LDR value: " + String(analogRead(PIN_LDR)), 0);

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
