#include <cstddef>

#include "PortduinoHardwareI2C.h"
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

PortduinoI2C::PortduinoI2C() : _allowAddressNotFound(false) {
}

void PortduinoI2C::begin() {
}

void PortduinoI2C::begin(uint8_t address) {
  UNUSED(address);
  notImplemented("I2C master mode not implemented!");
}

void PortduinoI2C::end() {
  _selectedDevice.reset();
}

void PortduinoI2C::setClock(uint32_t freq) {
  UNUSED(freq);
}

void PortduinoI2C::beginTransmission(uint8_t address) {
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

uint8_t PortduinoI2C::endTransmission(bool stopBit) {
  UNUSED(stopBit);
  if (_selectedDevice != 0) {
    _selectedDevice.reset();
    return 0;
  }
  return 2;
}

uint8_t PortduinoI2C::endTransmission(void) {
  return endTransmission(true);
}

size_t PortduinoI2C::requestFrom(uint8_t address, size_t len, bool stopBit) {
  UNUSED(address);
  UNUSED(len);
  UNUSED(stopBit);
  notImplemented("requestFrom");
  return 0;
}

size_t PortduinoI2C::requestFrom(uint8_t address, size_t len) {
  return requestFrom(address, len, true);
}

void PortduinoI2C::onReceive(void (*)(int)) {
  notImplemented("onReceive");
}

void PortduinoI2C::onRequest(void (*)(void)) {
  notImplemented("onRequest");
}

size_t PortduinoI2C::write(uint8_t data) {
  notImplemented("writei2c");
  if (!_selectedDevice) {
    log_e(SysI2C, "no I2C device selected!");
  }
  return _selectedDevice->write(data);
}

size_t PortduinoI2C::write(const uint8_t *buffer, size_t size) {
  for (size_t i = 0; i < size; i++) {
    write(buffer[i]);
  }
  return size;
}

int PortduinoI2C::available() {
  notImplemented("i2cavailable");
  return 0;
}

int PortduinoI2C::read() {
  notImplemented("writei2c");
  if (!_selectedDevice) {
    log_e(SysI2C, "no I2C device selected!");
  }
  return _selectedDevice->read();
}

int PortduinoI2C::peek() {
  notImplemented("i2cpeek");
  return -1;
}

void PortduinoI2C::addI2CDevice(std::shared_ptr<I2CDevice> device) {
  _devices.push_back(device);
}

void PortduinoI2C::allowAddressNotFound(bool allow) {
  _allowAddressNotFound = allow;
}

PortduinoI2C Wire;
} // namespace arduino
