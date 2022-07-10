#include <csignal>
#include <stdio.h>

#include "Utility.h"
#include "logging.h"

void notImplemented(const char *msg) {
  log_w(SysCore, "%s is not implemented", msg);
}

int checkNotNeg(int result, const char *msg, ...) {
  if (result < 0) {
    printf("Portduino notneg errno=%d: %s\n", errno, msg);
    throw Exception(msg);
  }
  return result;
}

int checkZero(int result, const char *msg, ...) {
  if (result != 0) {
    printf("Portduino checkzero %d: %s\n", result, msg);
    throw Exception(msg);
  }
  return result;
}

void debug() {
  std::raise(SIGINT);
}
