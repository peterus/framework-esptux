#include <argp.h>
#include <stdio.h>

#include "Arduino.h"
#include "FS/vfs_api.h"
#include "SimGPIO.h"
#include "logging.h"

#define LOOPDELAY 100

using namespace fs;

std::shared_ptr<VFSImpl> TuxVFS = std::make_shared<VFSImpl>();
FS                       TuxFS  = FS(TuxVFS);

void __attribute__((weak)) coreSetup() {
  log_i(SysCore, "No coreSetup() found, using default function...");
}

void __attribute__((weak)) coreInit() {
  log_i(SysCore, "No coreCustomInit() found, using default function...");
}

int main() {
  (void)millis(); // to start timer
  loggerInit();

  String fsRoot = ".ESPtux";
  mkdir(fsRoot.c_str(), 0700);
  fsRoot += "/default";
  mkdir(fsRoot.c_str(), 0700);

  log_i(SysCore, "ESPtux is starting up");
  log_i(SysCore, "VFS root at %s", fsRoot.c_str());

  TuxVFS->mountpoint(fsRoot.c_str());

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
