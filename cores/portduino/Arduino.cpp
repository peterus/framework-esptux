#include <argp.h>
#include <stdio.h>

#include "Arduino.h"
#include "PortduinoFS.h"
#include "PortduinoGPIO.h"
#include "logging.h"

#define LOOPDELAY 100

void __attribute__((weak)) portduinoSetup() {
  log_i(SysCore, "No portduinoSetup() found, using default function...");
}

void __attribute__((weak)) portduinoInit() {
  log_i(SysCore, "No portduinoCustomInit() found, using default function...");
}

int main() {
  loggerInit();

  String fsRoot = ".portduino";
  mkdir(fsRoot.c_str(), 0700);
  fsRoot += "/default";
  mkdir(fsRoot.c_str(), 0700);

  log_i(SysCore, "Portduino is starting up");
  log_i(SysCore, "VFS root at %s", fsRoot.c_str());

  portduinoVFS->mountpoint(fsRoot.c_str());

  portduinoInit();

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
