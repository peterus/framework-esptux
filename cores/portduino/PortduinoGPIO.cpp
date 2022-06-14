#include <assert.h>
#include <stdlib.h>

#include "Arduino.h"
#include "Common.h"
#include "PortduinoGPIO.h"
#include "Utility.h"
#include "logging.h"

#define NUM_GPIOS 64

static GPIOPinIf *pins[NUM_GPIOS];

void gpioInit() {
  for (size_t i = 0; i < NUM_GPIOS; i++)
    pins[i] = new SimGPIOPin(i, "Unbound");
}

void gpioIdle() {
  for (size_t i = 0; i < NUM_GPIOS; i++)
    pins[i]->refreshIfNeeded();
}

void gpioBind(GPIOPinIf *p) {
  assert(p->getPinNum() < NUM_GPIOS);
  pins[p->getPinNum()] = p;
}

GPIOPinIf *getGPIO(pin_size_t n) {
  assert(n < NUM_GPIOS);
  auto p = pins[n];

  assert(p);
  return p;
}

void pinMode(pin_size_t pinNumber, PinMode pinMode) {
  auto p = getGPIO(pinNumber);
  p->setPinMode(pinMode);
}

void digitalWrite(pin_size_t pinNumber, PinStatus status) {
  auto p = getGPIO(pinNumber);
  p->writePin(status);
}

PinStatus digitalRead(pin_size_t pinNumber) {
  auto p = getGPIO(pinNumber);
  auto r = p->readPin();
  return r;
}

int analogRead(pin_size_t pinNumber) {
  auto p = getGPIO(pinNumber);
  auto r = p->analogRead();
  log(SysGPIO, LogDebug, "analogRead(%d) -> %d", pinNumber, r);
  return r;
}

void analogWrite(pin_size_t pinNumber, int value) {
  auto p = getGPIO(pinNumber);
  log(SysGPIO, LogDebug, "analogWrite(%d) -> %d", pinNumber, value);
  p->analogWrite(value);
}

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode) {
  auto p = getGPIO(interruptNumber);
  p->attachInterrupt(callback, mode);
}

void detachInterrupt(pin_size_t interruptNumber) {
  auto p = getGPIO(interruptNumber);
  p->detachInterrupt();
}

pin_size_t digitalPinToInterrupt(pin_size_t pinNumber) {
  return pinNumber;
}
