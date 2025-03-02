#pragma once

// Inspired by
// https://deepbluembedded.com/stm32-servo-motor-control-with-pwm-servo-library-examples-code/

#include "Valve.h"

#define HBL388_OPERATING_FREQUENCY_HZ 333

#define HBL388_PSC 5
//#define HBL388_ARR 30029
#define HBL388_ARR 25000

#define HBL388_PWM_DUTY_CYCLE_MIN_CCR 0
#define HBL388_PWM_DUTY_CYCLE_MAX_CCR 30029

#define HBL388_ELAPSED_DELAY_MS 1
#define HBL388_ELAPSED_STEP 1000

extern void HBL388_init(Valve* instance);

extern void HBL388_gatherData(Valve* instance);

extern void HBL388_setDutyCycle(Valve* instance, uint32_t dutyCycle_pct);

extern void HBL388_tick(Valve* instance);