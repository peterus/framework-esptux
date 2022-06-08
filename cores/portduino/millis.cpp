#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

extern "C" unsigned long micros(void) {
  struct timeval te;
  gettimeofday(&te, NULL);
  unsigned long usecs = te.tv_sec * 1000000LL + te.tv_usec;
  return usecs;
}

extern "C" unsigned long millis(void) {
  static unsigned long startMsec = 0;
  struct timeval       te;
  gettimeofday(&te, NULL);

  unsigned long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;

  if (startMsec == 0)
    startMsec = milliseconds;

  return milliseconds - startMsec;
}
