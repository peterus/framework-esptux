#include "Wire.h"
#include "Utility.h"
#include "logging.h"

TwoWire::TwoWire() : _allowAddressNotFound(false) {
}

TwoWire::~TwoWire() {
}

void TwoWire::begin() {
}

void TwoWire::begin(uint8_t address) {
  UNUSED(address);
  notImplemented("TwoWire::I2C master mode");
}

void TwoWire::end() {
  _selectedDevice.reset();
}

void TwoWire::setClock(uint32_t freq) {
  UNUSED(freq);
}

void TwoWire::beginTransmission(uint8_t address) {
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

uint8_t TwoWire::endTransmission(bool stopBit) {
  UNUSED(stopBit);
  if (_selectedDevice != 0) {
    _selectedDevice.reset();
    return 0;
  }
  return 2;
}

uint8_t TwoWire::endTransmission(void) {
  return endTransmission(true);
}

size_t TwoWire::requestFrom(uint8_t address, size_t len, bool stopBit) {
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
  notImplemented("TwoWire::requestFrom");
  return 0;
}

size_t TwoWire::requestFrom(uint8_t address, size_t len) {
  return requestFrom(address, len, true);
}

void TwoWire::onReceive(void (*)(int)) {
  notImplemented("TwoWire::onReceive");
}

void TwoWire::onRequest(void (*)(void)) {
  notImplemented("TwoWire::onRequest");
}

size_t TwoWire::write(uint8_t data) {
  if (!_selectedDevice) {
    log_e(SysI2C, "no I2C device selected!");
  }
  return _selectedDevice->write(data);
}

size_t TwoWire::write(const uint8_t *buffer, size_t size) {
  for (size_t i = 0; i < size; i++) {
    write(buffer[i]);
  }
  return size;
}

int TwoWire::available() {
  notImplemented("TwoWire::available");
  return 0;
}

int TwoWire::read() {
  if (!_selectedDevice) {
    log_e(SysI2C, "no I2C device selected!");
  }
  return _selectedDevice->read();
}

int TwoWire::peek() {
  notImplemented("TwoWire::peek");
  return -1;
}

void TwoWire::addI2CDevice(std::shared_ptr<WireDevice> device) {
  _devices.push_back(device);
}

void TwoWire::allowAddressNotFound(bool allow) {
  _allowAddressNotFound = allow;
}

TwoWire Wire;
