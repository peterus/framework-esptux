#ifndef PORTDUINO_HARDWAREI2C_H_
#define PORTDUINO_HARDWAREI2C_H_

#include <cstdint>
#include <memory>

#include "HardwareI2C.h"
#include "Utility.h"

namespace arduino {

class I2CDevice {
public:
  I2CDevice(uint8_t address);

  uint8_t getAddress() const;

  virtual size_t write(uint8_t data) = 0;
  virtual int    read()              = 0;

private:
  const uint8_t _address;
};

class PortduinoI2C : public HardwareI2C {
public:
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

private:
  std::shared_ptr<I2CDevice> _selectedDevice;
};

extern PortduinoI2C Wire;

void addI2CDevice(std::shared_ptr<I2CDevice> device);

} // namespace arduino

#endif
