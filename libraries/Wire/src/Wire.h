#ifndef WIRE_H_
#define WIRE_H_

#include <cstdint>
#include <list>
#include <memory>

#include "Arduino.h"
#include "HardwareI2C.h"
#include "WireDevice.h"

class SimI2C : public HardwareI2C {
public:
  SimI2C();

  virtual void begin() final;
  virtual void begin(uint8_t address) final;

  virtual void end() final;

  virtual void setClock(uint32_t freq) final;

  virtual void    beginTransmission(uint8_t address) final;
  virtual uint8_t endTransmission(bool stopBit) final;
  virtual uint8_t endTransmission(void) final;

  virtual size_t requestFrom(uint8_t address, size_t len, bool stopBit) final;
  virtual size_t requestFrom(uint8_t address, size_t len) final;

  virtual void onReceive(void (*)(int)) final;
  virtual void onRequest(void (*)(void)) final;

  virtual size_t write(uint8_t) final;
  virtual size_t write(const uint8_t *buffer, size_t size) final;

  virtual int available() final;
  virtual int read() final;
  virtual int peek() final;

  // I2C sim handling functions - do not use in Arduino code!
  void addI2CDevice(std::shared_ptr<WireDevice> device);
  void allowAddressNotFound(bool allow = true);

private:
  bool _allowAddressNotFound;

  std::shared_ptr<WireDevice>            _selectedDevice;
  std::list<std::shared_ptr<WireDevice>> _devices;
};

extern SimI2C Wire;

#endif
