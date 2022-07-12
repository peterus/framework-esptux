#ifndef SIM_GPIO_H_
#define SIM_GPIO_H_

#include <assert.h>
#include <stdlib.h>

#include "Arduino.h"
#include "Common.h"
#include "Utility.h"
#include "logging.h"

void gpioInit();
void gpioIdle();

pin_size_t digitalPinToInterrupt(pin_size_t pin_number);

#endif
