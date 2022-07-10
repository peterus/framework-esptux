#include <cstdarg>
#include <stdio.h>

#include "SimSerial.h"
#include "Utility.h"

namespace arduino {
SimSerial Serial;

void SimSerial::begin(unsigned long baudrate) {
  begin(baudrate, SERIAL_8N1);
}

void SimSerial::begin(unsigned long baudrate, uint16_t config) {
  UNUSED(baudrate);
  UNUSED(config);
}

void SimSerial::end() {
}

int SimSerial::available(void) {
  return 0;
}

int SimSerial::peek(void) {
  return -1;
}

int SimSerial::read(void) {
  return -1;
}

void SimSerial::flush(void) {
}

size_t SimSerial::write(uint8_t c) {
  putchar(c);
  return 1;
}

SimSerial::operator bool() {
  return true;
}

#define MAX_STR_LEN 256

size_t SimSerial::printf(const char *format, ...) {
  char    buf[MAX_STR_LEN];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  write(buf);
  va_end(args);
  return strlen(buf);
}

} // namespace arduino
