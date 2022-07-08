#include <assert.h>

#include "SPIChip.h"
#include "SimSPI.h"
#include "Utility.h"
#include "logging.h"

SPIChip *spiChip;

namespace arduino {

uint8_t PortduinoSPI::transfer(uint8_t data) {
  uint8_t response;
  assert(spiChip);
  spiChip->transfer(&data, &response, 1, false);
  return response;
}

uint16_t PortduinoSPI::transfer16(uint16_t data) {
  UNUSED(data);
  notImplemented("transfer16");
  return 0x4242;
}

void PortduinoSPI::transfer(void *buf, size_t count) {
  UNUSED(buf);
  UNUSED(count);
  notImplemented("spi general transfer");
  assert(spiChip);
  // spiChip->transfer(buf, buf, count);
}

void PortduinoSPI::usingInterrupt(int interruptNumber) {
  UNUSED(interruptNumber);
}

void PortduinoSPI::notUsingInterrupt(int interruptNumber) {
  UNUSED(interruptNumber);
}

void PortduinoSPI::beginTransaction(SPISettings settings) {
  assert(settings.getBitOrder() == MSBFIRST);
  assert(settings.getDataMode() == SPI_MODE0);
}

void PortduinoSPI::endTransaction(void) {
  assert(spiChip);
}

void PortduinoSPI::attachInterrupt() {
}

void PortduinoSPI::detachInterrupt() {
}

void PortduinoSPI::begin() {
  if (!spiChip) {
    spiChip = new SimSPIChip();
  }
}

void PortduinoSPI::end() {
  if (spiChip) {
    delete spiChip;
    spiChip = NULL;
  }
}

PortduinoSPI SPI;

} // namespace arduino
