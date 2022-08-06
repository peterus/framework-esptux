#include "Arduino.h"
#include "SPI.h"
#include "logging.h"
#include <cstdint>

#define ARRAY_SIZE 10

class SPIDev : public SPIChip {
public:
  SPIDev(int8_t ss) : SPIChip(ss), _i(0) {
    std::fill(std::begin(_Buffer), std::begin(_Buffer) + ARRAY_SIZE, 0);
  }

  ~SPIDev() {
  }

  uint8_t transfer(const uint8_t buf) final {
    _Buffer[_i] = buf;
    _i++;
    if (_i > ARRAY_SIZE) {
      _i = 0;
    }
    return _Buffer[_i];
  }

private:
  uint8_t      _Buffer[ARRAY_SIZE];
  unsigned int _i;
};

void coreInit() {
  loggerSetLevel(SysI2C, LogInfo);
}

void coreSetup() {
  SPI.addSPIDevice(std::make_shared<SPIDev>(5));
}
