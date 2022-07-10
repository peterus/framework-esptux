#include <cstddef>

#include "SimI2C.h"
#include "Utility.h"
#include "logging.h"

namespace arduino {

I2CDevice::I2CDevice(uint8_t i2cAddress) : _i2cAddress(i2cAddress) {
}

I2CDevice::~I2CDevice() {
}

uint8_t I2CDevice::getAddress() const {
  return _i2cAddress;
}

void I2CDevice::begin(uint8_t registerAddress) {
  _registerAddress = registerAddress;
}

SimI2C::SimI2C() : _allowAddressNotFound(false) {
}

void SimI2C::begin() {
}

void SimI2C::begin(uint8_t address) {
  UNUSED(address);
  notImplemented("I2C master mode not implemented!");
}

void SimI2C::end() {
  _selectedDevice.reset();
}

void SimI2C::setClock(uint32_t freq) {
  UNUSED(freq);
}

void SimI2C::beginTransmission(uint8_t address) {
  for (std::shared_ptr<I2CDevice> device : _devices) {
    if (device->getAddress() == address) {
      _selectedDevice = device;
      return;
    }
  }
  if (_allowAddressNotFound) {
    log_d(SysI2C, "could not find I2C address: %d", address);
  } else {
    log_e(SysI2C, "could not find I2C address: %d", address);
  }
}

uint8_t SimI2C::endTransmission(bool stopBit) {
  UNUSED(stopBit);
  if (_selectedDevice != 0) {
    _selectedDevice.reset();
    return 0;
  }
  return 2;
}

uint8_t SimI2C::endTransmission(void) {
  return endTransmission(true);
}

size_t SimI2C::requestFrom(uint8_t address, size_t len, bool stopBit) {
  UNUSED(address);
  UNUSED(len);
  UNUSED(stopBit);
  notImplemented("requestFrom");
  return 0;
}

size_t SimI2C::requestFrom(uint8_t address, size_t len) {
  return requestFrom(address, len, true);
}

void SimI2C::onReceive(void (*)(int)) {
  notImplemented("onReceive");
}

void SimI2C::onRequest(void (*)(void)) {
  notImplemented("onRequest");
}

size_t SimI2C::write(uint8_t data) {
  notImplemented("writei2c");
  if (!_selectedDevice) {
    log_e(SysI2C, "no I2C device selected!");
  }
  return _selectedDevice->write(data);
}

size_t SimI2C::write(const uint8_t *buffer, size_t size) {
  for (size_t i = 0; i < size; i++) {
    write(buffer[i]);
  }
  return size;
}

int SimI2C::available() {
  notImplemented("i2cavailable");
  return 0;
}

int SimI2C::read() {
  notImplemented("writei2c");
  if (!_selectedDevice) {
    log_e(SysI2C, "no I2C device selected!");
  }
  return _selectedDevice->read();
}

int SimI2C::peek() {
  notImplemented("i2cpeek");
  return -1;
}

void SimI2C::addI2CDevice(std::shared_ptr<I2CDevice> device) {
  _devices.push_back(device);
}

void SimI2C::allowAddressNotFound(bool allow) {
  _allowAddressNotFound = allow;
}

SimI2C Wire;
} // namespace arduino
