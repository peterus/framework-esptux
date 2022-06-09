#include <sched.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "Common.h"
#include "Utility.h"

unsigned long micros(void) {
  struct timeval te;
  gettimeofday(&te, NULL);
  unsigned long usecs = te.tv_sec * 1000000LL + te.tv_usec;
  return usecs;
}

unsigned long millis(void) {
  static unsigned long startMsec = 0;
  struct timeval       te;
  gettimeofday(&te, NULL);

  unsigned long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;

  if (startMsec == 0)
    startMsec = milliseconds;

  return milliseconds - startMsec;
}

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
