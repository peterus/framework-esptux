#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <argp.h>

#include "ArduinoAPI.h"

using namespace arduino;

#include "FS/FS.h"

using namespace fs;

#include "SimI2C.h"
#include "SimSPI.h"
#include "SimSerial.h"

extern FS PortduinoFS;

extern void coreSetup();

extern void coreInit();

#endif
