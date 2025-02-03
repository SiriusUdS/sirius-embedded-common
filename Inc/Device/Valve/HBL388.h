#pragma once

// Inspired by
// https://deepbluembedded.com/stm32-servo-motor-control-with-pwm-servo-library-examples-code/

#include "Valve.h"

#define FREQUENCY_HZ 333
#define HBL388_PSC 8
#define ARR 32031
#define CLOCK_FREQUENCY_HZ 96000000

extern void HBL388_init(Valve* instance);

extern void HBL388_gatherData(Valve* instance);

extern void HBL388_setDutyCycle(Valve* instance, uint8_t dutyCycle_pct);