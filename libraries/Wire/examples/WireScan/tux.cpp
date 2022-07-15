#include "Arduino.h"
#include "Wire.h"
#include "logging.h"

class Memory : public I2CDevice {
public:
  Memory(uint8_t i2cAddress) : I2CDevice(i2cAddress) {
  }

  virtual size_t write(uint8_t data) final {
    _mem[_registerAddress] = data;
    _registerAddress++;
    return 1;
  }

  virtual int read() final {
    int data = _mem[_registerAddress];
    _registerAddress++;
    return data;
  }

private:
  int _mem[256];
};

void coreInit() {
  loggerSetLevel(SysI2C, LogInfo);
  Wire.allowAddressNotFound();
}

void coreSetup() {
  Wire.addI2CDevice(std::make_shared<Memory>(120));
  Wire.addI2CDevice(std::make_shared<Memory>(126));
  Wire.addI2CDevice(std::make_shared<Memory>(0x12));
}
