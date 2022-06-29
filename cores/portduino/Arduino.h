#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <argp.h>

#include "ArduinoAPI.h"
#include "PortduinoHardwareI2C.h"
#include "PortduinoHardwareSPI.h"
#include "PortduinoHardwareSerial.h"

using namespace arduino;

extern void portduinoSetup();

extern void portduinoInit();

#endif
