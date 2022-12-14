#include "util.h"
#include "Utility.h"
#include <csignal>
#include <stdio.h>

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
