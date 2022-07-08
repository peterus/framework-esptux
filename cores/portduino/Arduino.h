#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <argp.h>

#include "ArduinoAPI.h"
#include "SimI2C.h"
#include "SimSPI.h"
#include "SimSerial.h"

using namespace arduino;

extern void portduinoSetup();

extern void portduinoInit();

#endif
