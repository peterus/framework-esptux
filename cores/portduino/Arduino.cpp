#include <argp.h>
#include <stdio.h>

#include "Arduino.h"
#include "PortduinoFS.h"
#include "PortduinoGPIO.h"

#define LOOPDELAY 100

void __attribute__((weak)) portduinoSetup() {
  printf("No portduinoSetup() found, using default function...\n");
}

void __attribute__((weak)) portduinoCustomInit() {
  printf("No portduinoCustomInit() found, using default function...\n");
}

int main() {
  String fsRoot = ".portduino";
  mkdir(fsRoot.c_str(), 0700);
  fsRoot += "/default";
  mkdir(fsRoot.c_str(), 0700);

  printf("Portduino is starting up\n");
  printf("VFS root at %s\n", fsRoot.c_str());

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
