#include "Wire.h"
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

SimI2C::SimI2C() : _allowAddressNotFound(false) {
}

void SimI2C::begin() {
}

void SimI2C::begin(uint8_t address) {
  UNUSED(address);
  notImplemented("I2C master mode");
}

void SimI2C::end() {
  _selectedDevice.reset();
}

void SimI2C::setClock(uint32_t freq) {
  UNUSED(freq);
}

void SimI2C::beginTransmission(uint8_t address) {
  for (std::shared_ptr<WireDevice> device : _devices) {
    if (device->getAddress() == address) {
      _selectedDevice = device;
      _selectedDevice->resetRegisterAddress();
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
  UNUSED(stopBit);

  for (std::shared_ptr<WireDevice> device : _devices) {
    if (device->getAddress() == address) {
      _selectedDevice = device;
      _selectedDevice->resetRegisterAddress();
      return len;
    }
  }
  if (_allowAddressNotFound) {
    log_d(SysI2C, "could not find I2C address: %d", address);
  } else {
    log_e(SysI2C, "could not find I2C address: %d", address);
  }

  return 0;

  UNUSED(address);
  UNUSED(len);
  notImplemented("SimI2C::requestFrom");
  return 0;
}

size_t SimI2C::requestFrom(uint8_t address, size_t len) {
  return requestFrom(address, len, true);
}

void SimI2C::onReceive(void (*)(int)) {
  notImplemented("SimI2C::onReceive");
}

void SimI2C::onRequest(void (*)(void)) {
  notImplemented("SimI2C::onRequest");
}

size_t SimI2C::write(uint8_t data) {
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
  notImplemented("SimI2C::available");
  return 0;
}

int SimI2C::read() {
  if (!_selectedDevice) {
    log_e(SysI2C, "no I2C device selected!");
  }
  return _selectedDevice->read();
}

int SimI2C::peek() {
  notImplemented("SimI2C::peek");
  return -1;
}

void SimI2C::addI2CDevice(std::shared_ptr<WireDevice> device) {
  _devices.push_back(device);
}

void SimI2C::allowAddressNotFound(bool allow) {
  _allowAddressNotFound = allow;
}

SimI2C Wire;
