#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <argp.h>

#include "ArduinoAPI.h"
#include "HardwareSPI.h"
#include "LinuxSerial.h"
#include "SimHardwareI2C.h"

extern HardwareSPI SPI;

using namespace arduino;

typedef HardwareI2C TwoWire;

inline pin_size_t digitalPinToInterrupt(pin_size_t pinNumber) {
  return pinNumber;
}

extern void portduinoSetup();

extern void portduinoCustomInit();

void portduinoAddArguments(const struct argp_child &child, void *childArguments);

void getMacAddr(uint8_t *dmac);

#endif
