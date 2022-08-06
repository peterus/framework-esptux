#include <assert.h>
#include <cstddef>
#include <utility>

#include "Arduino.h"
#include "SPI.h"
#include "SPIChip.h"
#include "Utility.h"
#include "logging.h"

SimSPI::SimSPI() : _ss(-1) {
}

void SimSPI::begin() {
  begin(18, 19, 23, 5);
}

void SimSPI::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss) {
  UNUSED(sck);
  UNUSED(miso);
  UNUSED(mosi);
  _ss = ss;
}

void SimSPI::end() {
}

uint8_t SimSPI::transfer(uint8_t data) {
  std::shared_ptr<SPIChip> spi_chip = getActiveSPIChip();
  return spi_chip->transfer(data);
}

uint16_t SimSPI::transfer16(uint16_t data) {
  UNUSED(data);
  notImplemented("transfer16");
  return 0x0000;
}

void SimSPI::transfer(void *buf, size_t count) {
  for (size_t i = 0; i < count; i++) {
    transfer(((uint8_t *)buf)[i]);
  }
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
}

void SimSPI::attachInterrupt() {
}

void SimSPI::detachInterrupt() {
}

void SimSPI::addSPIDevice(std::shared_ptr<SPIChip> device) {
  _devices.push_back(device);
}

std::shared_ptr<SPIChip> SimSPI::getActiveSPIChip() {
  for (std::shared_ptr<SPIChip> device : _devices) {
    if (digitalRead(device->getChipSelect()) == LOW) {
      return device;
    }
  }
  log_e(SysSPI, "no SPI device found!");
  return 0;
}

int8_t SimSPI::pinSS() const {
  return _ss;
}

SimSPI SPI;
