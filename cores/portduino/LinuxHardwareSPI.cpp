#include <assert.h>

#include "HardwareSPI.h"
#include "SPIChip.h"
#include "Utility.h"
#include "logging.h"

SPIChip *spiChip;

namespace arduino {

uint8_t HardwareSPI::transfer(uint8_t data) {
  uint8_t response;
  assert(spiChip);
  spiChip->transfer(&data, &response, 1, false);
  return response;
}

uint16_t HardwareSPI::transfer16(uint16_t data) {
  notImplemented("transfer16");
  return 0x4242;
}

void HardwareSPI::transfer(void *buf, size_t count) {
  notImplemented("spi general transfer");
  assert(spiChip);
  spiChip->transfer(buf, buf, count);
}

void HardwareSPI::usingInterrupt(int interruptNumber) {
}

void HardwareSPI::notUsingInterrupt(int interruptNumber) {
}

void HardwareSPI::beginTransaction(SPISettings settings) {
  assert(settings.bitOrder == MSBFIRST);
  assert(settings.dataMode == SPI_MODE0);
}

void HardwareSPI::endTransaction(void) {
  assert(spiChip);
}

void HardwareSPI::attachInterrupt() {
}

void HardwareSPI::detachInterrupt() {
}

void HardwareSPI::begin() {
  if (!spiChip) {
    spiChip = new SimSPIChip();
  }
}

void HardwareSPI::end() {
  if (spiChip) {
    delete spiChip;
    spiChip = NULL;
  }
}

} // namespace arduino

HardwareSPI SPI;
