#include "PortduinoHardwareI2C.h"

namespace arduino {

void PortduinoI2C::begin() {
  notImplemented("i2cbegin");
}

void PortduinoI2C::begin(uint8_t address) {
  notImplemented("i2cslave begin");
}

void PortduinoI2C::end() {
  notImplemented("i2cend");
}

void PortduinoI2C::setClock(uint32_t freq) {
  notImplemented("i2csetClock");
}

void PortduinoI2C::beginTransmission(uint8_t address) {
  // FIXME - implement
}

uint8_t PortduinoI2C::endTransmission(bool stopBit) {
  // notImplemented("i2cEndTransmission"); FIXME implement
  return I2cAddrNAK; // Claim everyone naks
}

uint8_t PortduinoI2C::endTransmission(void) {
  return endTransmission(true);
}

size_t PortduinoI2C::requestFrom(uint8_t address, size_t len, bool stopBit) {
  notImplemented("requestFrom");
  return 0;
}

size_t PortduinoI2C::requestFrom(uint8_t address, size_t len) {
  notImplemented("requestFrom");
  return 0;
}

void PortduinoI2C::onReceive(void (*)(int)) {
  notImplemented("onReceive");
}

void PortduinoI2C::onRequest(void (*)(void)) {
  notImplemented("onRequest");
}

size_t PortduinoI2C::write(uint8_t) {
  notImplemented("writei2c");
  return 0;
}

size_t PortduinoI2C::write(const uint8_t *buffer, size_t size) {
  notImplemented("writeNi2c");
  return 0;
}

int PortduinoI2C::available() {
  notImplemented("i2cavailable");
  return 0;
}

int PortduinoI2C::read() {
  notImplemented("i2cread");
  return -1;
}

int PortduinoI2C::peek() {
  notImplemented("i2cpeek");
  return -1;
}

PortduinoI2C Wire;
} // namespace arduino
