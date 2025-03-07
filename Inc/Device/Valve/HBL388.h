#pragma once

// Inspired by
// https://deepbluembedded.com/stm32-servo-motor-control-with-pwm-servo-library-examples-code/

#include "Valve.h"

#define HBL388_OPERATING_FREQUENCY_HZ 333

#define HBL388_PSC 3
#define HBL388_ARR 54059

#define HBL388_PWM_DUTY_CYCLE_MIN_CCR 0
#define HBL388_PWM_DUTY_CYCLE_MAX_CCR HBL388_ARR

#define HBL388_PWM_OPEN_DUTY_CYCLE_PCT  72
#define HBL388_PWM_CLOSE_DUTY_CYCLE_PCT 28

#define HBL388_ELAPSED_DELAY_MS 1
#define HBL388_STEP 1000

extern void HBL388_init(Valve* instance);

extern void HBL388_setDutyCycle(Valve* instance, uint32_t dutyCycle_pct);

extern void HBL388_close(Valve* instance, uint32_t timestamp_ms);

extern void HBL388_open(Valve* instance, uint32_t timestamp_ms);

extern void HBL388_tick(Valve* instance);