#pragma once

// Inspired by
// https://deepbluembedded.com/stm32-servo-motor-control-with-pwm-servo-library-examples-code/

#include "Valve.h"

#define HBL388_OPERATING_FREQUENCY_HZ 333
#define HBL388_PSC 8
#define HBL388_ARR 32031

#define HBL388_PWM_DUTY_CYCLE_MIN 0
#define HBL388_PWM_DUTY_CYCLE_MAX 32031

#define CLOCK_FREQUENCY_HZ 96000000

extern void HBL388_init(Valve* instance);

extern void HBL388_gatherData(Valve* instance);

extern void HBL388_setDutyCycle(Valve* instance, uint32_t dutyCycle_pct);