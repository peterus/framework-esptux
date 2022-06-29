#include <csignal>
#include <stdio.h>

#include "Utility.h"
#include "logging.h"

void notImplemented(const char *msg) {
  log_w(arduino::SysCore, "%s is not implemented", msg);
}

int portduinoCheckNotNeg(int result, const char *msg, ...) {
  if (result < 0) {
    printf("Portduino notneg errno=%d: %s\n", errno, msg);
    throw Exception(msg);
  }
  return result;
}

int portduinoCheckZero(int result, const char *msg, ...) {
  if (result != 0) {
    printf("Portduino checkzero %d: %s\n", result, msg);
    throw Exception(msg);
  }
  return result;
}

void portduinoDebug() {
  std::raise(SIGINT);
}
