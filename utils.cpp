#include "utils.hpp"

void debug(String msg, LogLevel lvl = LogLevel.Info) {
  if(!SERIAL_ENABLED || SERIAL_LOG_LEVEL > lvl)
    return;

  switch(lvl) {
    case Debug: Serial.print("[Debug] "); break;
    case Info:  Serial.print("[Info]  "); break;
    case Error: Serial.print("‼ [ERROR] "); break;
  }

  Serial.println(msg);
}
