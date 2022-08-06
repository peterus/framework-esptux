#ifndef SIM_HARDWARE_H_
#define SIM_HARDWARE_H_

#include <assert.h>
#include <cstdint>
#include <list>
#include <memory.h>
#include <tuple>
#include <utility>

#include "Arduino.h"
#include "HardwareSPI.h"
#include "SPIChip.h"
#include "Utility.h"
#include "logging.h"

class SimSPI : public HardwareSPI {
public:
  SimSPI();

  virtual void begin() final;
  void         begin(int8_t sck, int8_t miso = -1, int8_t mosi = -1, int8_t ss = -1);
  virtual void end() final;

  virtual uint8_t  transfer(uint8_t data) final;
  virtual uint16_t transfer16(uint16_t data) final;
  virtual void     transfer(void *buf, size_t count) final;

  // Transaction Functions
  virtual void usingInterrupt(int interruptNumber) final;
  virtual void notUsingInterrupt(int interruptNumber) final;
  virtual void beginTransaction(SPISettings settings) final;
  virtual void endTransaction(void) final;

  // SPI Configuration methods
  virtual void attachInterrupt() final;
  virtual void detachInterrupt() final;

  // SPI sim handling functions - do not use in Arduino code!
  void                     addSPIDevice(std::shared_ptr<SPIChip> device);
  std::shared_ptr<SPIChip> getActiveSPIChip();

  int8_t pinSS() const;

private:
  std::list<std::shared_ptr<SPIChip>> _devices;
  int8_t                              _ss;
};

extern SimSPI SPI;

#endif
