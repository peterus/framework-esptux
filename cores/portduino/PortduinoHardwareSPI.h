#ifndef PORTUINO_HARDWARE_H_
#define PORTUINO_HARDWARE_H_

#include <assert.h>

#include "HardwareSPI.h"
#include "SPIChip.h"
#include "Utility.h"
#include "logging.h"

namespace arduino {

class SimHardwareSPI : public HardwareSPI {
public:
  virtual uint8_t  transfer(uint8_t data);
  virtual uint16_t transfer16(uint16_t data);
  virtual void     transfer(void *buf, size_t count);

  // Transaction Functions
  virtual void usingInterrupt(int interruptNumber);
  virtual void notUsingInterrupt(int interruptNumber);
  virtual void beginTransaction(SPISettings settings);
  virtual void endTransaction(void);

  // SPI Configuration methods
  virtual void attachInterrupt();
  virtual void detachInterrupt();

  virtual void begin();
  virtual void end();
};

extern SimHardwareSPI SPI;

} // namespace arduino

#endif
