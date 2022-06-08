#ifndef PORTDUINO_LINUXSERIAL_H
#define PORTDUINO_LINUXSERIAL_H

#include "HardwareSerial.h"

namespace arduino {
class LinuxSerial : public HardwareSerial {
public:
  virtual void   begin(unsigned long baudrate) final;
  virtual void   begin(unsigned long baudrate, uint16_t config) final;
  virtual void   end() final;
  virtual int    available(void) final;
  virtual int    peek(void) final;
  virtual int    read(void) final;
  virtual void   flush(void) final;
  virtual size_t write(uint8_t) final;
  using Print::write;
  virtual operator bool() final;
};

extern LinuxSerial Serial;
} // namespace arduino

#endif
