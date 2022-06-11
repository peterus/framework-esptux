#include <argp.h>
#include <stdio.h>

#include "Arduino.h"
#include "PortduinoFS.h"
#include "PortduinoGPIO.h"

#define LOOPDELAY 100

pin_size_t digitalPinToInterrupt(pin_size_t pinNumber) {
  return pinNumber;
}

void __attribute__((weak)) portduinoSetup() {
  printf("No portduinoSetup() found, using default function...\n");
}

void __attribute__((weak)) portduinoCustomInit() {
  printf("No portduinoCustomInit() found, using default function...\n");
}

int main() {
  unsigned int hwId   = 1;
  String       fsRoot = ".portduino";
  mkdir(fsRoot.c_str(), 0700);
  fsRoot += "/default";
  mkdir(fsRoot.c_str(), 0700);

  printf("Portduino is starting, HWID=%d, VFS root at %s\n", hwId, fsRoot.c_str());

  portduinoVFS->mountpoint(fsRoot.c_str());

  portduinoCustomInit();

  gpioInit();
  portduinoSetup();
  setup();
  while (true) {
    gpioIdle();
    loop();
    delay(LOOPDELAY);
  }
  return 0;
}
