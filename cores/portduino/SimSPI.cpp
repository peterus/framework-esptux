#include <assert.h>

#include "SPIChip.h"
#include "SimSPI.h"
#include "Utility.h"
#include "logging.h"

SPIChip *spiChip;

namespace arduino {

uint8_t SimSPI::transfer(uint8_t data) {
  uint8_t response;
  assert(spiChip);
  spiChip->transfer(&data, &response, 1, false);
  return response;
}

uint16_t SimSPI::transfer16(uint16_t data) {
  UNUSED(data);
  notImplemented("transfer16");
  return 0x4242;
}

void SimSPI::transfer(void *buf, size_t count) {
  UNUSED(buf);
  UNUSED(count);
  notImplemented("spi general transfer");
  assert(spiChip);
  // spiChip->transfer(buf, buf, count);
}

void SimSPI::usingInterrupt(int interruptNumber) {
  UNUSED(interruptNumber);
}

void SimSPI::notUsingInterrupt(int interruptNumber) {
  UNUSED(interruptNumber);
}

void SimSPI::beginTransaction(SPISettings settings) {
  assert(settings.getBitOrder() == MSBFIRST);
  assert(settings.getDataMode() == SPI_MODE0);
}

void SimSPI::endTransaction(void) {
  assert(spiChip);
}

void SimSPI::attachInterrupt() {
}

void SimSPI::detachInterrupt() {
}

void SimSPI::begin() {
  if (!spiChip) {
    spiChip = new SimSPIChip();
  }
}

void SimSPI::end() {
  if (spiChip) {
    delete spiChip;
    spiChip = NULL;
  }
}

SimSPI SPI;

} // namespace arduino
