#include "Utility.h"
#include <Print.h>

#include <cstdarg>

#define MAX_STR_LEN 256

size_t Print::printf(const char *format, ...) {
  char    buf[MAX_STR_LEN];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  write(buf);
  va_end(args);
}
