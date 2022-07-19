#include "WireDevice.h"
#include "Utility.h"
#include "logging.h"

WireDevice::WireDevice(uint8_t i2cAddress) : _i2cAddress(i2cAddress) {
}

WireDevice::~WireDevice() {
}

uint8_t WireDevice::getAddress() const {
  return _i2cAddress;
}

void WireDevice::begin(uint8_t registerAddress) {
  _registerAddress = registerAddress;
}

void WireDevice::resetRegisterAddress() {
  _registerAddress = 0;
}
