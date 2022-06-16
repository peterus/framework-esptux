#include "Arduino.h"

#include "Utility.h"
#include "logging.h"

namespace arduino {

String getLogLevelText(const LogLevel level) {
  switch (level) {
  case LogVerbose:
    return "V";
  case LogDebug:
    return "D";
  case LogInfo:
    return "I";
  case LogWarn:
    return "W";
  case LogError:
    return "E";
  default:
    return " ";
  }
}

String getLogSystemText(const LogSystem system) {
  switch (system) {
  case SysCore:
    return "CORE";
  case SysGPIO:
    return "GPIO";
  case SysI2C:
    return "I2C";
  case SysSPI:
    return "SPI";
  case SysInterrupt:
    return "INT";
  case SysWifi:
    return "WIFI";
  default:
    return "APP" + String(system - SysApp0);
  }
}

void logv(const LogSystem system, const LogLevel level, const char *fmt, va_list args) {
  char buf[256];
  vsnprintf(buf, sizeof(buf), fmt, args);
  Serial.print("[");
  Serial.print(getLogLevelText(level));
  Serial.print("][");
  Serial.print(getLogSystemText(system));
  Serial.print("]");
  Serial.print(buf);
  Serial.println();
}

void log(const LogSystem system, const LogLevel level, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, level, fmt, args);
  va_end(args);
}

void log_e(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogError, fmt, args);
  va_end(args);
}

void log_w(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogWarn, fmt, args);
  va_end(args);
}

void log_i(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogInfo, fmt, args);
  va_end(args);
}

void log_d(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogDebug, fmt, args);
  va_end(args);
}

void log_v(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogVerbose, fmt, args);
  va_end(args);
}

} // namespace arduino
