#ifndef WIRE_DEVICE_H_
#define WIRE_DEVICE_H_

#include <cstddef>
#include <cstdint>

class WireDevice {
public:
  WireDevice(uint8_t i2cAddress);
  virtual ~WireDevice();

  uint8_t getAddress() const;

  virtual void begin(uint8_t registerAddress);
  void         resetRegisterAddress();

  virtual size_t write(uint8_t data) = 0;
  virtual int    read()              = 0;

protected:
  uint8_t _registerAddress;

private:
  const uint8_t _i2cAddress;
};

#endif
