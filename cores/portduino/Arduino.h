#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <argp.h>

#include "ArduinoAPI.h"
#include "FS/FS.h"
#include "SimI2C.h"
#include "SimSPI.h"
#include "SimSerial.h"

using namespace arduino;

extern fs::FS PortduinoFS;

extern void coreSetup();

extern void coreInit();

#endif
