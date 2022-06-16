#include <cstddef>
#include <list>

#include "PortduinoHardwareI2C.h"
#include "Utility.h"

namespace arduino {

std::list<std::shared_ptr<I2CDevice>> _I2CDevices;

void PortduinoI2C::begin() {
}

void PortduinoI2C::begin(uint8_t address) {
  UNUSED(address);
  portduinoError("I2C master mode not implemented!");
}

void PortduinoI2C::end() {
  _selectedDevice.reset();
}

void PortduinoI2C::setClock(uint32_t freq) {
  UNUSED(freq);
}

void PortduinoI2C::beginTransmission(uint8_t address) {
  for (std::shared_ptr<I2CDevice> device : _I2CDevices) {
    if (device->getAddress() == address) {
      _selectedDevice = device;
      return;
    }
  }
  portduinoError("could not found I2C address");
}

uint8_t PortduinoI2C::endTransmission(bool stopBit) {
  _selectedDevice.reset();
  UNUSED(stopBit);
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
    portduinoError("no I2C device selected!");
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
    portduinoError("no I2C device selected!");
  }
  return _selectedDevice->read();
}

int PortduinoI2C::peek() {
  notImplemented("i2cpeek");
  return -1;
}

I2CDevice::I2CDevice(uint8_t address) : _address(address) {
}

uint8_t I2CDevice::getAddress() const {
  return _address;
}

void addI2CDevice(std::shared_ptr<I2CDevice> device) {
  _I2CDevices.push_back(device);
}

PortduinoI2C Wire;
} // namespace arduino
