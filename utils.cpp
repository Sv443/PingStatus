#include "utils.hpp"

void debug(String msg, uint8_t lvl) {
  if(!SERIAL_ENABLED || SERIAL_LOG_LEVEL > lvl)
    return;

  switch(lvl) {
    case 0: Serial.print("[Debug] "); break;
    case 1: Serial.print("[Info]  "); break;
    case 2: Serial.print("‼ [ERROR] "); break;
  }

  Serial.println(msg);
}
