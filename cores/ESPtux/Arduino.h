#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <argp.h>

#include "ArduinoAPI.h"

using namespace arduino;

#include "FS/FS.h"

using namespace fs;

#include "SimSerial.h"

extern FS TuxFS;

extern void coreSetup();

extern void coreInit();

#endif
