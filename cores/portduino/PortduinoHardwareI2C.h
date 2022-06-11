#ifndef PORTDUINO_HARDWAREI2C_H_
#define PORTDUINO_HARDWAREI2C_H_

#include "HardwareI2C.h"
#include "Utility.h"

namespace arduino {

enum ResultI2c
{
  I2cSuccess = 0,
  I2cTooLong,
  I2cAddrNAK,
  I2cDataNAK,
  I2cOtherError
};

class SimHardwareI2C : public HardwareI2C {
public:
  virtual void begin() {
    notImplemented("i2cbegin");
  }

  virtual void begin(uint8_t address) {
    notImplemented("i2cslave begin");
  }

  virtual void end() {
    notImplemented("i2cend");
  }

  virtual void setClock(uint32_t freq) {
    notImplemented("i2csetClock");
  }

  virtual void beginTransmission(uint8_t address) {
    // FIXME - implement
  }

  virtual uint8_t endTransmission(bool stopBit) {
    // notImplemented("i2cEndTransmission"); FIXME implement
    return I2cAddrNAK; // Claim everyone naks
  }

  virtual uint8_t endTransmission(void) {
    return endTransmission(true);
  }

  virtual size_t requestFrom(uint8_t address, size_t len, bool stopBit) {
    notImplemented("requestFrom");
    return 0;
  }

  virtual size_t requestFrom(uint8_t address, size_t len) {
    notImplemented("requestFrom");
    return 0;
  }

  virtual void onReceive(void (*)(int)) {
    notImplemented("onReceive");
  }

  virtual void onRequest(void (*)(void)) {
    notImplemented("onRequest");
  }

  virtual size_t write(uint8_t) {
    notImplemented("writei2c");
    return 0;
  }

  virtual size_t write(const uint8_t *buffer, size_t size) {
    notImplemented("writeNi2c");
    return 0;
  }

  virtual int available() {
    notImplemented("i2cavailable");
    return 0;
  }

  virtual int read() {
    notImplemented("i2cread");
    return -1;
  }

  virtual int peek() {
    notImplemented("i2cpeek");
    return -1;
  }
};

extern SimHardwareI2C Wire;

} // namespace arduino

#endif
