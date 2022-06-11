#include <assert.h>

#include "PortduinoHardwareSPI.h"
#include "SPIChip.h"
#include "Utility.h"
#include "logging.h"

SPIChip *spiChip;

namespace arduino {

uint8_t SimHardwareSPI::transfer(uint8_t data) {
  uint8_t response;
  assert(spiChip);
  spiChip->transfer(&data, &response, 1, false);
  return response;
}

uint16_t SimHardwareSPI::transfer16(uint16_t data) {
  notImplemented("transfer16");
  return 0x4242;
}

void SimHardwareSPI::transfer(void *buf, size_t count) {
  notImplemented("spi general transfer");
  assert(spiChip);
  // spiChip->transfer(buf, buf, count);
}

void SimHardwareSPI::usingInterrupt(int interruptNumber) {
}

void SimHardwareSPI::notUsingInterrupt(int interruptNumber) {
}

void SimHardwareSPI::beginTransaction(SPISettings settings) {
  assert(settings.getBitOrder() == MSBFIRST);
  assert(settings.getDataMode() == SPI_MODE0);
}

void SimHardwareSPI::endTransaction(void) {
  assert(spiChip);
}

void SimHardwareSPI::attachInterrupt() {
}

void SimHardwareSPI::detachInterrupt() {
}

void SimHardwareSPI::begin() {
  if (!spiChip) {
    spiChip = new SimSPIChip();
  }
}

void SimHardwareSPI::end() {
  if (spiChip) {
    delete spiChip;
    spiChip = NULL;
  }
}

SimHardwareSPI SPI;

} // namespace arduino
