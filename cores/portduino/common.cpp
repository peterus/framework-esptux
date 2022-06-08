#include <sched.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Common.h"
#include "Utility.h"

void delay(unsigned long milliSec) {
  usleep(milliSec * 1000);
}

void delayMicroseconds(unsigned int usec) {
  usleep(usec);
}

void yield(void) {
  sched_yield();
}

long random(long max) {
  return random(0, max);
}

long random(long min, long max) {
  return rand() % (max - min) + min;
}

void randomSeed(unsigned long s) {
  srand(s);
}

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
  notImplemented("tone");
}

void noTone(uint8_t _pin) {
  notImplemented("noTone");
}
