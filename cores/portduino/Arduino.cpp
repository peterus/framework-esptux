#include <argp.h>
#include <stdio.h>

#include "Arduino.h"
#include "SimGPIO.h"
#include "logging.h"
#include "vfs_api.h"

#define LOOPDELAY 100

using namespace fs;

std::shared_ptr<VFSImpl> portduinoVFS = std::make_shared<VFSImpl>();
FS                       PortduinoFS  = FS(portduinoVFS);

void __attribute__((weak)) coreSetup() {
  log_i(SysCore, "No coreSetup() found, using default function...");
}

void __attribute__((weak)) coreInit() {
  log_i(SysCore, "No coreCustomInit() found, using default function...");
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

  coreInit();

  gpioInit();
  coreSetup();

  setup();
  while (true) {
    gpioIdle();
    loop();
    delay(LOOPDELAY);
  }
  return 0;
}
