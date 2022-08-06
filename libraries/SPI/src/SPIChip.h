#ifndef SPI_CHIP_H_
#define SPI_CHIP_H_

#include "Utility.h"
#include <cstdint>

class SPIChip {
public:
  SPIChip(int8_t ss);
  virtual ~SPIChip();

  virtual uint8_t transfer(const uint8_t buf) = 0;

  int8_t getChipSelect() const;

private:
  int8_t _ss;
};

#endif
