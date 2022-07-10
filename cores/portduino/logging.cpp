#include <ostream>
#include <sstream>

#include "Arduino.h"

#include "Utility.h"
#include "logging.h"

constexpr int MAX_SYSTEM_LOG = 100;

LogLevel _levels[MAX_SYSTEM_LOG];

void loggerInit() {
  std::fill_n(_levels, MAX_SYSTEM_LOG, LogInfo);
}

void loggerSetLevel(const LogSystem system, const LogLevel level) {
  _levels[system] = level;
}

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

void logv(const LogSystem system, const LogLevel level, bool exception, const char *fmt, va_list args) {
  if (_levels[system] > level) {
    return;
  }

  char buf[256];
  vsnprintf(buf, sizeof(buf), fmt, args);

  std::stringstream ss;
  ss << "[" << getLogLevelText(level).c_str() << "][" << getLogSystemText(system).c_str() << "] ";
  ss << buf;

  Serial.println(ss.str().c_str());

  if (exception) {
    throw Exception(ss.str());
  }
}

void log(const LogSystem system, const LogLevel level, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, level, false, fmt, args);
  va_end(args);
}

void log_e(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogError, true, fmt, args);
  va_end(args);
}

void log_w(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogWarn, false, fmt, args);
  va_end(args);
}

void log_i(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogInfo, false, fmt, args);
  va_end(args);
}

void log_d(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogDebug, false, fmt, args);
  va_end(args);
}

void log_v(const LogSystem system, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  logv(system, LogVerbose, false, fmt, args);
  va_end(args);
}
