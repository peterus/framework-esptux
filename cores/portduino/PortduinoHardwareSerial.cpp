#include <stdio.h>

#include "PortduinoHardwareSerial.h"
#include "Utility.h"

namespace arduino {
PortduinoSerial Serial;

void PortduinoSerial::begin(unsigned long baudrate) {
  begin(baudrate, SERIAL_8N1);
}

void PortduinoSerial::begin(unsigned long baudrate, uint16_t config) {
  UNUSED(baudrate);
  UNUSED(config);
}

void PortduinoSerial::end() {
}

int PortduinoSerial::available(void) {
  return 0;
}

int PortduinoSerial::peek(void) {
  return -1;
}

int PortduinoSerial::read(void) {
  return -1;
}

void PortduinoSerial::flush(void) {
}

size_t PortduinoSerial::write(uint8_t c) {
  putchar(c);
  return 1;
}

PortduinoSerial::operator bool() {
  return true;
}

} // namespace arduino
