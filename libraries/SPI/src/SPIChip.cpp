#include "SPIChip.h"
#include "Utility.h"

SPIChip::SPIChip(int8_t ss) : _ss(ss) {
}

SPIChip::~SPIChip() {
}

int8_t SPIChip::getChipSelect() const {
  return _ss;
}
