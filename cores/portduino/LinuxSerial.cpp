#include <stdio.h>

#include "LinuxSerial.h"

namespace arduino {
LinuxSerial Serial;

void LinuxSerial::begin(unsigned long baudrate) {
  begin(baudrate, SERIAL_8N1);
}
void LinuxSerial::begin(unsigned long baudrate, uint16_t config) {
}

void LinuxSerial::end() {
}

int LinuxSerial::available(void) {
  return 0;
}

int LinuxSerial::peek(void) {
  return -1;
}

int LinuxSerial::read(void) {
  return -1;
}

void LinuxSerial::flush(void) {
}

size_t LinuxSerial::write(uint8_t c) {
  putchar(c);
  return 1;
}

LinuxSerial::operator bool() {
  return true;
}
} // namespace arduino
