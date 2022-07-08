#include <assert.h>
#include <stdlib.h>
#include <vector>

#include "Arduino.h"
#include "Common.h"
#include "SimGPIO.h"
#include "Utility.h"
#include "logging.h"

class GPIOPin {
public:
  GPIOPin(pin_size_t number, String name) : _number(number), _name(name), _silent(false), _mode(INPUT_PULLUP), _newStatus(HIGH), _status(HIGH), _isrPinStatus(RISING), _isrCallbackFunc(NULL) {
  }

  pin_size_t getPinNum() const {
    return _number;
  }

  const char *getName() const {
    return _name.c_str();
  }

  void setPinMode(PinMode mode) {
    _mode = mode;
    if (!_silent)
      log(SysGPIO, LogInfo, "setPinMode(%s, %d, %d)", getName(), getPinNum(), mode);
  }

  PinStatus readPin() {
    refreshState();
    if (!_silent) {
      log(SysGPIO, LogInfo, "readPin(%s, %d, %d)", getName(), getPinNum(), _status);
    }
    return _status;
  }

  void writePin(PinStatus status) {
    assert(status == HIGH || status == LOW);
    _newStatus = status;
    if (!_silent) {
      log(SysGPIO, LogInfo, "writePin(%s, %d, %d)", getName(), getPinNum(), _newStatus);
    }
  }

  int analogRead() {
    notImplemented("gpio:analogRead");
    return 4242;
  }

  void analogWrite(int v) {
    UNUSED(v);
    notImplemented("gpio:refreshState");
  }

  void attachInterrupt(voidFuncPtr callbackFunc, PinStatus status) {
    _isrCallbackFunc = callbackFunc;
    _isrPinStatus    = status;
  }

  void detachInterrupt() {
    _isrCallbackFunc = NULL;
  }

  void refreshState() {
    if (_isrCallbackFunc) {
      callISR();
    }
    _status = _newStatus;
  }

private:
  pin_size_t _number;
  String     _name;
  bool       _silent;

  PinMode   _mode;
  PinStatus _newStatus;
  PinStatus _status;

  PinStatus   _isrPinStatus;
  voidFuncPtr _isrCallbackFunc;

  void callISR() {
    if (_isrPinStatus == RISING && _newStatus == HIGH && _status == LOW) {
      log(SysGPIO, LogDebug, "GPIOPin::callISR(RISING, %s, %d)", getName(), getPinNum());
      _isrCallbackFunc();
    } else if (_isrPinStatus == FALLING && _newStatus == LOW && _status == HIGH) {
      log(SysGPIO, LogDebug, "GPIOPin::callISR(FALLING, %s, %d)", getName(), getPinNum());
      _isrCallbackFunc();
    } else if (_isrPinStatus == CHANGE && _newStatus != _status) {
      log(SysGPIO, LogDebug, "GPIOPin::callISR(CHANGE, %s, %d)", getName(), getPinNum());
      _isrCallbackFunc();
    }
  }
};

#define NUM_GPIOS 64
static std::vector<GPIOPin> pins;

void gpioInit() {
  for (size_t i = 0; i < NUM_GPIOS; i++) {
    pins.push_back(GPIOPin(i, "Unbound"));
  }
}

void gpioIdle() {
  for (size_t i = 0; i < pins.size(); i++) {
    pins[i].refreshState();
  }
}

void pinMode(pin_size_t pinNumber, PinMode pinMode) {
  pins[pinNumber].setPinMode(pinMode);
}

void digitalWrite(pin_size_t pinNumber, PinStatus status) {
  pins[pinNumber].writePin(status);
}

PinStatus digitalRead(pin_size_t pinNumber) {
  return pins[pinNumber].readPin();
}

int analogRead(pin_size_t pinNumber) {
  return pins[pinNumber].analogRead();
}

void analogWrite(pin_size_t pinNumber, int value) {
  pins[pinNumber].analogWrite(value);
}

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode) {
  pins[interruptNumber].attachInterrupt(callback, mode);
}

void detachInterrupt(pin_size_t interruptNumber) {
  pins[interruptNumber].detachInterrupt();
}

pin_size_t digitalPinToInterrupt(pin_size_t pinNumber) {
  return pinNumber;
}
