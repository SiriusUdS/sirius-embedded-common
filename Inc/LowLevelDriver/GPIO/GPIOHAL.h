#pragma once

#include "GPIO.h"

extern void GPIOHAL_init(GPIO* instance);

extern int8_t GPIOHAL_read(GPIO* instance);

extern void GPIOHAL_write(GPIO* instance, uint8_t value);