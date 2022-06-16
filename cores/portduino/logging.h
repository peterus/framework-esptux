#ifndef LOGGING_H_
#define LOGGING_H_

namespace arduino {

enum LogLevel
{
  LogVerbose,
  LogDebug,
  LogInfo,
  LogWarn,
  LogError
};

enum LogSystem
{
  SysCore,
  SysGPIO,
  SysI2C,
  SysSPI,
  SysInterrupt,
  SysWifi,
  SysFS,
  // Ids greater than 1000 are used for application specific purposes
  SysApp0 = 1000
};

void log(const LogSystem system, const LogLevel level, const char *fmt, ...) __attribute__((format(printf, 3, 4)));

void log_e(const LogSystem system, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
void log_w(const LogSystem system, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
void log_i(const LogSystem system, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
void log_d(const LogSystem system, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
void log_v(const LogSystem system, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

} // namespace arduino

#endif
