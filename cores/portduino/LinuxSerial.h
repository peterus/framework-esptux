#ifndef PORTDUINO_LINUXSERIAL_H
#define PORTDUINO_LINUXSERIAL_H

#include "HardwareSerial.h"

namespace arduino {
class LinuxSerial : public HardwareSerial {
public:
  virtual void   begin(unsigned long baudrate, uint16_t config = SERIAL_8N1);
  virtual void   end();
  virtual int    available(void);
  virtual int    peek(void);
  virtual int    read(void);
  virtual void   flush(void);
  virtual size_t write(uint8_t);
  using Print::write;
  virtual operator bool();
};

extern LinuxSerial Serial;
} // namespace arduino

#endif
